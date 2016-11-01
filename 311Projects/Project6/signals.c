#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <signal.h>
#include <errno.h>
#include "signals.h"
#include <unistd.h>

/* GLOBAL VARIABLES
*   allSigs and queue need to be accessed by the signal handlers 
*/
int allSigs = 0;
int queue[50];

/* Handler for SIGALRM signal 
*   Very simple message to user saying alarm was handled
*/
void alarm_Handler (int sig);               

/* handler for SIGUSR1 signal 
*   generates a new alarm, adds it to the end of the queue,
*   the the queue is sorted to mainain call order.   
*/
void userSig1_Handler(int sig); 

/* Sorts the queue, to make sure the alarms are called in order 
*   PRECONDITION: A array, along with size is passed in
*   POSTCONDITION: Array is sorted in increasing order
*/
void sort(int a[], int size);               

/* Because the for loop is based on a global variable
*   I believe the compiler was optimizing the for loop so the 
*   count was not being updated. 
*   This is a simple retrieval method to get value for the 
*   global variable "allSigs"
*/
int getCount();

int main(void)
{

    int numAlarms;
    int callErr;
    int randomNum, currTime;
    int i;
    int PID;
    int fromNow;



    srand(time(NULL));

    struct sigaction alrm_act;
    struct sigaction sig1_handler;


    /*      Set ALARM signal handler.     */
    alrm_act.sa_handler = (void(*)(int))alarm_Handler;
    sigemptyset(&alrm_act.sa_mask);
    alrm_act.sa_flags = 0;
    callErr = sigaction (SIGALRM, &alrm_act, NULL);
    if (callErr == -1) {
        printf ("sig2:  error (%d) setting handler.\n", callErr);
    }

     /* Setup SIGUSR1 signal handler  */
    sig1_handler.sa_handler = (void(*)(int))userSig1_Handler;
    sigemptyset(&sig1_handler.sa_mask);
    sig1_handler.sa_flags = 0;
    callErr = sigaction (SIGUSR1, &sig1_handler, NULL);
    if (callErr == -1) {
        printf ("sig2:  error (%d) setting handler.\n", callErr);
    }
    PID = getpid();

    /* Get Number of alarms from user   */
    printf("This process' ID is %d\n", PID);
    printf("Please specify the number of alarms you would like to set?\n :");
    scanf("%d", &numAlarms);

    currTime = time(NULL);
    printf("Current Time:%d \n",currTime);

    printf("Setting alarms...");
    /* putting alarm times in the queue */
    for (i = 0; i < numAlarms; i++) {
        randomNum = rand()% (MAX_TIME) + i;
        currTime = time(NULL);

        queue[allSigs] = randomNum + currTime;
        printf("(%d, %d)\n",i, (currTime + randomNum) );

        ++allSigs; /* Incrementing the amount of signals */
    }

    /* Sort the order of the calls to be in order according to time */
    sort(queue,allSigs);

    /* This for loop does a sequence of alarm sets and pauses */
    for (i = 0; i < getCount(); ++i) {

        currTime = time(NULL);          /* Get current Time */
        fromNow = queue[i] - currTime;  /* Get the relative time from when the alarm was set */

        printf("time = %d\n", currTime);

        if (fromNow > 0 ) {
            
            printf("WARNING: Alarm in %d seconds\n", fromNow);
            alarm (fromNow);
            callErr = pause();
            
            if ( callErr == -1 && errno != EINTR ) {
                printf ("Something went wrong...\n errno = %d\n", errno);
                exit (2);
            }

        } else {
          
            printf("Uh oh... you missed alarm #%d\n", i+1);
        }

        printf("%d signals left... \n",(allSigs - (i + 1)));

    }

    return 0;
}

void sort(int a[], int count) {
    
    int i = 0;
    int j = 0;
    int position;
    int temp;

    for ( i = 0 ; i < (count -1) ; i++ )
    {
        position = i;

        for ( j = i + 1 ; j < count ; j++ )
        {
            if (a[position] > a[j] )
                position = j;
        }
        if ( position != i )
        {
            temp = a[i];
            a[i] = a[position];
            a[position] = temp;
        }
    }

}

void alarm_Handler (int sig) {

    printf ("ALARM:  Signal received at %d.\n", time(NULL));
}

void userSig1_Handler(int sig) {
    int randomNum, currTime;

    randomNum = rand() % (MAX_TIME) + 5;
    currTime = time(NULL);
    printf ("SIGUSR1:  Signal received at %d.\n", time(NULL));

    printf("Added alarm to go off at %d\n",(randomNum + currTime));

    queue[allSigs] = currTime+randomNum; /* Add new time to queue */
    ++allSigs;                           /* Increment # of signals */
    printf("Now there are %d total signals\n", allSigs);
    sort(queue,allSigs);                 /* Sort array to maintain order */
}

int getCount() {
    return allSigs;
}
