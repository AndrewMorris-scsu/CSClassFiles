#include <string.h>
#include "NumberBase.h"

void ShowMenu();
void DisplayNumber(int Input);
unsigned int DigitToZero(unsigned int Input, int nth);


int main(void)
{   //Initialize variables
    int MenuOption = 0; //1-5 menu options
    unsigned int Input = 0;      //Input number from user
    int nth = 0;        //Used for zeroing 'nth' digit function (DigitToZero)


    printf("Welcome to Andrew Morris' implementation of Project 2\n");
    printf("Input a number:");
    scanf("%d", &Input );   //User's input number to perform operations on
    ShowMenu();
    scanf("%d",&MenuOption);//Initial menu option

    while(MenuOption != 5){

            switch(MenuOption){
            case 1:{
                DisplayNumber(Input);
                break;
            }
            case 2:{
                Input = SHIFTL(Input);
                DisplayNumber(Input);
                break;
            }
            case 3:{
                Input = SHIFTR(Input);
                DisplayNumber(Input);
                break;
            }
            case 4:{

                printf("What digit would you like to be zero?\n");
                scanf("%d",&nth);
                int i = 0;
                for(i; i < nth;i++){
                    Input = SHIFTR(Input);
                }
                Input = KILLR(Input);
                i = 0;
                for(i;i < nth+1;i++){
                    Input = SHIFTL(Input);
                }
                DisplayNumber(Input);
                break;
            }
            case 5:{
                break;
            }
            default: {
                printf("Please select a valid menu option... \n");

            }
            }
            ShowMenu();
            scanf("%d",&MenuOption);
    }

        return 0;
}

void ShowMenu(){
    printf("Select option\n");
    if(BASE == 2){//Binary
    printf("1 - Display number in binary \n");
    }
    if(BASE == 16){//Hexadecimal
    printf("1 - Display number in hexadecimal \n");
    }
    printf("2 - Shift left circular on digit\n");
    printf("3 - Shift right circular one digit\n");
    printf("4 - Set digit n to zero\n");
    printf("5 - Exit\n");
}
void DisplayNumber(int Input){
    if(BASE == 2){//Print Binary Number
    unsigned int a[32];
    //Convert Input to binary and display.
    //Input passed by value, will not be usable after
    //conversion in this function
       int i = BINARYSIZE -1;
       for(i;i>=0; i--){
          unsigned int temp = 0;
          unsigned int Two = 2; //Unsigned int for division
           if(Input == 0){ //Fill in remaining zeros
               a[i] = 0;
           }else{
           temp = (Input%2)*(Input%2);
           a[i] = temp;

           Input= (Input)/Two;
           }
       }
       i=0;
       for(i;i<BINARYSIZE; i++){
           printf("%i",a[i]);
       }
       printf("\n");

    }
    if(BASE == 16){//Print Hexadecimal Number
     printf( "%#010x\n", Input );
    }

}

unsigned int DigitToZero(unsigned int Input, int nth){

        return Input;
}
