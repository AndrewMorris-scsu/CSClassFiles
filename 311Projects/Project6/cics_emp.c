/*
 * NAME:        cics_emp.c - Sample implementation of EMP interface functions
 * VERSION:     1.12.1.9
 *                                                         
 *   (C) COPYRIGHT International Business Machines Corp.   
 *   1993, 2015                                            
 *   All Rights Reserved                                   
 *   Licensed Materials - Property of IBM                  
 *   5724-B44                                              
 *                                                         
 *   US Government Users Restricted Rights -               
 *   Use, duplication or disclosure restricted by          
 *   GSA ADP Schedule Contract with IBM Corp.              
 *                                                         
 *                                                                       
 *            NOTICE TO USERS OF THE SOURCE CODE EXAMPLES                
 *                                                                       
 * INTERNATIONAL BUSINESS MACHINES CORPORATION PROVIDES THE SOURCE CODE  
 * EXAMPLES, BOTH INDIVIDUALLY AND AS ONE OR MORE GROUPS, AS IS          
 * WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED,            
 * INCLUDING, BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF               
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE ENTIRE     
 * RISK AS TO THE QUALITY AND PERFORMANCE OF THE SOURCE CODE EXAMPLES,   
 * BOTH INDIVIDUALLY AND AS ONE OR MORE GROUPS, IS WITH YOU.  SHOULD     
 * ANY PART OF THE SOURCE CODE EXAMPLES PROVE DEFECTIVE, YOU (AND NOT    
 * IBM) ASSUME THE ENTIRE COST OF ALL NECESSARY SERVICING, REPAIR OR     
 * CORRECTION.  THIS PROGRAM MAY BE USED, EXECUTED, COPIED, MODIFIED     
 * AND DISTRIBUTED WITHOUT ROYALTY FOR THE PURPOSE OF DEVELOPING,        
 * MARKETING, OR DISTRIBUTING.                                           
 *                                                                       
 *                                                                       
 *
 *
 * SYNOPSIS:
 *
 * #include <cicstype.h>
 * #include <cics_emp.h>
 *
 * CICS_EMP_Return_t
 * CICS_EMP_Init        (IN    struct CICS_EMP_RegionData       *RegionData,
 *                       INOUT struct CICS_EMP_Functions        *Functions,
 *                       INOUT void                             **SaveSpace,
 *                       OUT   int                              *ErrorCode,
 *                       IN    struct CICS_EMP_PerformanceClass *SystemData,
 *                       IN    struct cics_eib                  *EIB,
 *                       IN    const struct CICS_EMP_Map        Dictionary[]);
 *
 * CICS_EMP_Return_t
 * CICS_EMP_EnterAPI    (IN    struct CICS_EMP_ENTER_API_Data   *EnterData,
 *                       INOUT void                             **SaveSpace,
 *                       OUT   int                              *ErrorCode);
 *
 * CICS_EMP_Return_t
 * CICS_EMP_WriteRecord (OUT   void                             **UserData,
 *                       OUT   int                              *UserDataLength,
 *                       IN    struct CICS_EMP_PerformanceClass *SystemData,
 *                       IN    int                              UnSupportedFields[],
 *                       INOUT void                             **SaveSpace,
 *                       OUT   int                              *ErrorCode,
 *                       IN    const struct CICS_EMP_Map        Dictionary[]);
 *
 * CICS_EMP_Return_t
 * CICS_EMP_ReStart     (IN    enum CICS_EMP_Finish             Action,
 *                       INOUT void                             **SaveSpace,
 *                       OUT   int                              *ErrorCode);
 *
 * void *CICS_EMP_Lookup(IN  int                              FID,
 *                       IN  const struct CICS_EMP_Map        Dictionary[],
 *                       IN  struct CICS_EMP_PerformanceClass *SystemData,
 *                       OUT int                              *Mask);
 * DESCRIPTION:
 *
 * These functions define the interface to the User EMP module.
 *
 * :hp3.CICS_EMP_Init:ehp3.
 *
 * This is the main entry point to the User EMP module.  It is invoked at the
 * start of each task if monitoring is enabled.  It performs three functions:
 * :ol.
 * :li.Determines if monitoring is required.
 * :li.Initialises any monitoring data used by the other User EMP
 * functions.
 * :li.If monitoring is required, it returns the address of those functions
 * to the caller in the :hp2.Functions:ehp2 parameter.
 * :eol.
 *
 * The :hp2.RegionData:ehp2. parameter can be used to log information
 * about the region from which this function was called, since the same
 * ULM may be used by many CICS regions.
 *
 * The parameter :hp2.SaveSpace:ehp2. allows the initialisation function to
 * pass the address of its private data area to the other ULM functions
 * (since static data cannot be used inside the ULM).  Normally, this space
 * will be :hp4.malloc'd:ehp4. during initialisation and :hp4.free'd:ehp4.
 * on task termination.  The returned address of this data is saved in the
 * Monitoring TCA structure for the task.  A copy of this value is passed
 * to the other ULM functions, which can be updated.  The new value (or old
 * value if not changed) is copied back to the TCA entry on completion of
 * the ULM function.
 *
 * The :hp2.ErrorCode:ehp2. parameter allows the function to return an error
 * code which is written as part of the log message when an return code other
 * than :hp4.CICS_EMP_RETURN_OK:ehp4. is returned.
 *
 * :hp3.CICS_EMP_EnterAPI:ehp3.
 *
 * This function processes the EXEC CICS ENTER API function.  The
 * information from the EXEC CICS ENTER API parameters is passed in the
 * :hp2.EnterData:ehp2. parameter.  The functionality of the entry point
 * is entirely user defined.  The function returns the appropriate
 * instructions to the calling function on completion.
 *
 * The :hp2.SaveSpace:ehp2. parameter contains the address of the ULM's
 * private data for this task.  The :hp2.ErrorCode:ehp2. parameter allows
 * the function to return an error code which is written as part of the
 * log message when an return code other than :hp4.CICS_EMP_RETURN_OK:ehp4.
 * or :hp4.CICS_EMP_RETURN_WRITE:ehp4. is returned.
 *
 * :hp3.CICS_EMP_WriteRecord:ehp3.
 *
 * This function is called to return the User Data buffer to be appended to
 * a monitoring record.  If the returned buffer address is NULL or the
 * length is zero, no user monitoring data is appended to the system
 * information.  The functionality of this entry is entirely user defined.
 * However, it should include stopping clocks if appropriate.
 *
 * The :hp2.SaveSpace:ehp2. parameter contains the address of the ULM's
 * private data for this task.  The :hp2.ErrorCode:ehp2. parameter allows
 * the function to return an error code which is written as part of the
 * log message when an return code other than :hp4.CICS_EMP_RETURN_OK:ehp4.
 * is returned.
 *
 * :hp2.UnSupportedFields:ehp2. is a null-delimited array of
 * CICS_EMP_PerformanceClass record field numbers. Each
 * entry in this array corresponds to an information field in the
 * CICS_EMP_PerformanceClass record which is not supported in the current
 * system environment. If this array is empty, then all fields are
 * supported. This array allows the user routine to distinguish between
 * a field which contains zero because no data has been collected and a
 * field which contains zero becuase it is not supported.
 *
 * :hp3.CICS_EMP_ReStart:ehp3.
 *
 * This function is called either when a monitoring record has been
 * successfully written to allow the restart of user clocks etc, or
 * when monitoring is complete for a task (either at the end of the
 * task or &infev. has detected an error) to allow the user functions
 * to release any resources acquired by the :hp2.CICS_EMP_Init:ehp2.
 * function.
 *
 * The :hp2.SaveSpace:ehp2. parameter contains the address of the ULM's
 * private data for this task.  The :hp2.ErrorCode:ehp2. parameter allows
 * the function to return an error code which is written as part of the
 * log message when an return code other than :hp4.CICS_EMP_RETURN_OK:ehp4.
 * is returned.
 *
 * :hp3.CICS_EMP_Lookup:ehp3.
 *
 * This function allows monitoring programs to access the SystemData without
 * needing to be recompiled for each release of CICS. It does this by using
 * a Dictionary provided as a parameter on the call to CICS_EMP_Init and
 * CICS_EMP_WriteRecord.
 *
 * This looks up the required CICS_EMP_FID value in the dictionary to
 * find its offset in the SystemData and then returns the address of
 * the item in the SystemData. It will return NULL if no match of the FID is
 * made.
 *
 * CAVEATS/WARNINGS:
 * The CICS shared region must be detached before calling these
 * functions. Any data stored in the shared region which is required by
 * these functions must be copied into local memory before being passed to
 * the User EMP functions.
 *
 * If a user function returns either :hp2.CICS_EMP_RETURN_FAIL:ehp2. or
 * :hp2.CICS_EMP_RETURN_DISABLE:ehp2., the user function is assumed to
 * have released any resources required and :hp2.CICS_EMP_ReStart:ehp2. will
 * not be invoked to release any resources.
 *
 * The pointer passed in the :hp2.SaveSpace:ehp2. parameter must be used
 * consistently between all four of the ULM functions otherwise pointer
 * alignment problems may arise.
 *
 * This code provides examples of the functionality that can be provided
 * via the ULM.
 *
 * RETURNED VALUES:
 *
 * :hp3.CICS_EMP_Init:ehp3.
 * :ul.
 * :li.
 * :hp2.CICS_EMP_RETURN_OK:ehp2. - The initialisation completed successfully.
 * :li.
 * :hp2.CICS_EMP_RETURN_FAIL:ehp2. - The initialisation detected an error.
 * User EMP are disabled for this region.
 * :li.
 * :hp2.CICS_EMP_RETURN_DISABLE:ehp2. - The initialisation completed
 * successfully.  However, monitoring is to be disabled for this
 * task.
 * :eul.
 * If :hp2.CICS_EMP_RETURN_OK:ehp2. is returned, the address of the
 * :hp4.CICS_EMP_EnterAPI:ehp4., :hp4.CICS_EMP_WriteRecord:ehp4. and
 * :hp4.CICS_EMP_ReStart:ehp4.  functions are returned in the
 * :hp2.Functions:ehp2. parameter.  In all other cases, the return value
 * of this parameter is ignored.
 *
 * :hp3.CICS_EMP_EnterAPI:ehp3.
 * :ul.
 * :li.
 * :hp2.CICS_EMP_RETURN_OK:ehp2. - The function completed successfully.
 * :li.
 * :hp2.CICS_EMP_RETURN_FAIL:ehp2. - The function detected an error.
 * User EMP are disabled for this task.
 * :li.
 * :hp2.CICS_EMP_RETURN_DISABLE:ehp2. - The function completed
 * successfully.  However, monitoring is to be disabled
 * for this task.
 * :li.
 * :hp2.CICS_EMP_RETURN_WRITE:ehp2. - The function completed successfully.
 * However, a monitoring record is to be written at this point.
 * This return value results in a call to :hp4.CICS_EMP_WriteRecord:ehp4.
 * to get the user data record.
 * :eul.
 *
 * :hp3.CICS_EMP_WriteRecord:ehp3.
 * :ul.
 * :li.
 * :hp2.CICS_EMP_RETURN_OK:ehp2. - The function completed successfully.
 * :li.
 * :hp2.CICS_EMP_RETURN_FAIL:ehp2. - The function detected an error.
 * User EMP are disabled for this task and no user data is written.
 * :li.
 * :hp2.CICS_EMP_RETURN_DISABLE:ehp2. - The function completed successfully.
 * However, no monitoring record is to be written at this point.
 * :eul.
 * If :hp2.CICS_EMP_RETURN_OK:ehp2. is returned, the User Data record and
 * its length are returned in the :hp2.UserData:ehp2. and
 * :hp2.UserDataLength:ehp2. parameter.  If either of these parameters is
 * NULL, only the system monitoring data is written to the file.  In all
 * other cases, the return value of these parameters is ignored.
 *
 * :hp3.CICS_EMP_ReStart:ehp3.
 * :ul.
 * :li.
 * :hp2.CICS_EMP_RETURN_OK:ehp2. - The function completed successfully.
 * :li.
 * :hp2.CICS_EMP_RETURN_FAIL:ehp2. - The function detected an error.
 * User EMP are disabled for this task.
 * :li.
 * :hp2.CICS_EMP_RETURN_DISABLE:ehp2. - The function completed successfully.
 * However, User EMP are disabled for this task.
 * :eul.
 *
 * RELATED INFORMATION:
 *
 * This code provides examples of the functionality that can be provided
 * via the ULM.
 *
 */


#include <cicstype.h> /* CICS-supplied datatypes */
#include <cics_samples.h> /* CICS-supplied macro definitions */
#include <stdlib.h>
#include <string.h>

#include <cics_emp.h>
#include <cics_emp_tdq.h>

void *CICS_EMP_Lookup( IN int FID,
                       IN const struct CICS_EMP_Map Dictionary[],
                       IN struct CICS_EMP_PerformanceClass *SystemData,
                       OUT int *Mask);
/*
 * Define the data structures for the ULM record.
 */

struct CICS_EMP_Record
{
    cics_ulong_t Clk_Counter1; /* Clock 1 counter      */
    cics_ulong_t Clk_Time1; /* Clock 1 value        */
    cics_ulong_t Clk_Counter2; /* Clock 2 counter      */
    cics_ulong_t Clk_Time2; /* Clock 2 value        */
    cics_slong_t Counter1r; /* Counter 1            */
    cics_slong_t Counter2r; /* Counter 2            */
    cics_slong_t Counter3r; /* Counter 3            */
};

/*
 * Define the data structures for the ULM save area.
 */

struct CICS_EMP_DataArea
{
    CICS_EMP_EventTime_t Clock1; /* Clock 1              */
    CICS_EMP_EventTime_t Clock2; /* Clock 1              */
    cics_slong_t Counter1; /* Counter 1            */
    cics_slong_t Counter2; /* Counter 2            */
    cics_slong_t Counter3; /* Counter 3            */
    int Active; /* Clock 1 active flag  */
    struct CICS_EMP_Record Record; /* The record           */
};

/*
 * Initialisation function
 */
CICS_EMP_Return_t
CICS_EMP_Init (IN struct CICS_EMP_RegionData *RegionData,
                        INOUT struct CICS_EMP_Functions *Functions,
                        INOUT void **SaveSpace,
                        OUT int *ErrorCode,
                        IN struct CICS_EMP_PerformanceClass *SystemData,
                        IN struct cics_eib *EIB,
                        IN const struct CICS_EMP_Map Dictionary[])
{
    /*ARGSUSED*/
    void *DataSpace; /* Our data space               */

/* Get some space */

    DataSpace = (void *)malloc(sizeof (struct CICS_EMP_DataArea));
    memset(DataSpace, 0, sizeof (struct CICS_EMP_DataArea));

/* Check to see if we got it */

    if (DataSpace == NULL)
    {
        *ErrorCode = 1;
        *SaveSpace = NULL;
        return CICS_EMP_RETURN_FAIL;
    }

    *SaveSpace = DataSpace;
    Functions->CICS_EMP_EnterAPI = CICS_EMP_EnterAPI;
    Functions->CICS_EMP_WriteRecord = CICS_EMP_WriteRecord;
    Functions->CICS_EMP_ReStart = CICS_EMP_ReStart;


    return CICS_EMP_RETURN_OK;
}


/*
 * EXEC CICS ENTER API Processing
 */


CICS_EMP_Return_t
CICS_EMP_EnterAPI (IN struct CICS_EMP_ENTER_API_Data *EnterData,
                         INOUT void **SaveSpace,
                         OUT int *ErrorCode)
{
    struct CICS_EMP_DataArea *LocalData;

    LocalData = (struct CICS_EMP_DataArea *)*SaveSpace;

/* Check initialisation OK */

     if (*SaveSpace == NULL)
     {
        *ErrorCode = 1;
        return CICS_EMP_RETURN_FAIL;
     }

/* Switch on the EMP ID */

    switch (EnterData->ID)
    {
        case 1: /* EMP 1 - write the record     */
            return CICS_EMP_RETURN_WRITE;


        case 2: /* EMP 2 - start or stop the    */
                                        /* clock depending on EnterName */
            if (strncmp (EnterData->EntryName, "START    ",
                         CICS_EMP_ENTRY_NAME_LEN) == 0)
            {
                LocalData->Active = 1;
                CICS_EMP_StartClock (&(LocalData->Clock1),
                                     CICS_EMP_CLOCK_TYPE_ELAPSED);
            }

            else if (strncmp (EnterData->EntryName, "STOP     ",
                         CICS_EMP_ENTRY_NAME_LEN) == 0)
            {
                LocalData->Active = 0;
                CICS_EMP_StopClock (&(LocalData->Clock1));
            }


            else /* Write some message ?         */
            {
            }

            return CICS_EMP_RETURN_OK;

        case 3: /* Add Data 1 field             */
            LocalData->Counter1 += EnterData->Data1;
            return CICS_EMP_RETURN_OK;

        case 4: /* Save Data 2 field            */
            LocalData->Counter2 = EnterData->Data2;
            return CICS_EMP_RETURN_OK;

        case 5: /* EMP 5 - Increment a counter  */
            ++(LocalData->Counter3);
            return CICS_EMP_RETURN_OK;

        case 6: /* EMP 6 - Disable monitoring   */
            free(LocalData);

            *ErrorCode = 2;
            return CICS_EMP_RETURN_DISABLE;

        case 7: /* EMP 7 - time a write         */
            CICS_EMP_StartClock (&(LocalData->Clock2),
                                     CICS_EMP_CLOCK_TYPE_ELAPSED);
            return CICS_EMP_RETURN_WRITE;

        case 8: /* EMP 8 - disable the ULM      */
            free(LocalData);

            *ErrorCode = 3;
            return CICS_EMP_RETURN_FAIL;

        default: /* Any other - ignore           */
            return CICS_EMP_RETURN_OK;
    }
}

/*
 * Write Record function
 */

CICS_EMP_Return_t
CICS_EMP_WriteRecord (OUT void **UserData,
                         OUT int *UserDataLength,
                         IN struct
                               CICS_EMP_PerformanceClass *SystemData,
                         IN int UnSupportedFields[],
                         INOUT void **SaveSpace,
                         OUT int *ErrorCode,
                         IN const struct CICS_EMP_Map Dictionary[])
{
    struct CICS_EMP_DataArea *LocalData;
    int i; /* loop counter */
    cics_char_t * RecordType;
    cics_char_t * UserID;

    RecordType = (cics_char_t *)CICS_EMP_Lookup(CICS_EMP_FID_RECORD_TYPE,
                                         Dictionary, SystemData, NULL);

    UserID = (cics_char_t *)CICS_EMP_Lookup(CICS_EMP_FID_USER_ID,
                                         Dictionary, SystemData, NULL);

    LocalData = (struct CICS_EMP_DataArea *)*SaveSpace;

/* Disable monitoring if we are not a ULM or end of task record */

    if ((*RecordType != CICS_EMP_REC_TYPE_ULM) &&
        (*RecordType != CICS_EMP_REC_TYPE_END))
    {
        free(LocalData);

        *ErrorCode = 4;
        return CICS_EMP_RETURN_DISABLE;
    }

/* If we are root or the data area does not exist - disable ULM */

    else if ((strncmp(UserID, "root", 4) == 0) || (*SaveSpace == NULL))
    {

/* Free the memory we acquired */

        if (*SaveSpace != NULL)
        {
            free(LocalData);
        }

        *ErrorCode = 5;
        *(UserData) = NULL;
        *UserDataLength = 0;
        return CICS_EMP_RETURN_FAIL;
    }

/* Verify that required fields in the PerformanceClass record are available */

    i = 0;
    while(UnSupportedFields[i] != 0)
    {

/* We are only interested in the swap count field, so if it is not      */
/* available clean up and quit.                                         */

        if(UnSupportedFields[i] == CICS_EMP_FID_SWAP_COUNT)
        {

/* Free the memory we acquired */

            if (*SaveSpace != NULL)
            {
                free(LocalData);
            }

            *ErrorCode = 7;
            *(UserData) = NULL;
            *UserDataLength = 0;
            return CICS_EMP_RETURN_FAIL;
        }
    }

/* Set up to return our record.  Stop our first clock and set up the record */

    CICS_EMP_StopClock (&(LocalData->Clock1));

    LocalData->Record.Clk_Counter1 = LocalData->Clock1.Clock.Counter;
    LocalData->Record.Clk_Time1 = LocalData->Clock1.Clock.TotalTime;

    LocalData->Record.Clk_Counter2 = LocalData->Clock2.Clock.Counter;
    LocalData->Record.Clk_Time2 = LocalData->Clock2.Clock.TotalTime;

    LocalData->Record.Counter1r = LocalData->Counter1;
    LocalData->Record.Counter2r = LocalData->Counter2;
    LocalData->Record.Counter3r = LocalData->Counter3;

/* Return the record address and length */

    *(UserData) = (void *)&(LocalData->Record);
    *UserDataLength = sizeof(struct CICS_EMP_Record);
    return CICS_EMP_RETURN_OK;
}

/*
 * Cleanup and Restart
 */

CICS_EMP_Return_t
CICS_EMP_ReStart (IN enum CICS_EMP_Finish Action,
                         INOUT void **SaveSpace,
                         OUT int *ErrorCode)
{
    struct CICS_EMP_DataArea *LocalData;

    LocalData = (struct CICS_EMP_DataArea *)*SaveSpace;

/* Check initialisation OK */

    if (*SaveSpace == NULL)
    {
        *ErrorCode = 6;
        return CICS_EMP_RETURN_FAIL;
    }

/* Decide what to do based on what we are asked to do */

    switch (Action) /* Switch on action             */
    {

/* Just written a record - restart our clocks and reset the counters */

        case CICS_EMP_FINISH_RESTART:
            LocalData->Counter1 = 0;
            LocalData->Counter2 = 0;
            LocalData->Counter3 = 0;

/* Restart clock 1 if it is active */

            if (LocalData->Active)
            {
                CICS_EMP_StartClock (&(LocalData->Clock1),
                                     CICS_EMP_CLOCK_TYPE_ELAPSED);
                LocalData->Active = 0;
            }

/* Stop clock 2 */

            CICS_EMP_StopClock (&(LocalData->Clock2));
            return CICS_EMP_RETURN_OK;

/* Clean up - Monitoring has detected some error, therefore release our
 * data space
 */

        case CICS_EMP_FINISH_CLEANUP:

            free(LocalData);

            return CICS_EMP_RETURN_OK;
    }

/* Unexpected code - just report it */

    *ErrorCode = Action;
    return CICS_EMP_RETURN_FAIL;
}

void *CICS_EMP_Lookup( IN int FID,
                       IN const struct CICS_EMP_Map Dictionary[],
                       IN struct CICS_EMP_PerformanceClass *SystemData,
                       OUT int *Mask)
{
    while ( ((Dictionary->Mask & CICS_EMP_FID_MASK) != FID) &&
             (Dictionary->Mask != ~0) )
    {
        Dictionary++;
    }

    if (Dictionary->Mask == ~0)
    {
        if (Mask != NULL) *Mask = 0;
        return NULL;
    }
    else
    {
        if (Mask != NULL) *Mask = Dictionary->Mask;
        return (void *)( ((cics_char_t *)SystemData) + Dictionary->Offset );
    }
}
