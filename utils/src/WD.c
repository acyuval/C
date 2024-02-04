/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/

#include <assert.h> /* assert			  */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>


#include <ctype.h>
#include <pthread.h> 
#include <stdatomic.h> 

#include "scheduler.h"

/******************************************************************************
*							 DECLARATION								 		  * 
******************************************************************************/


/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/
main(int argc, char ** argv, char ** envp)
{
    scheduler_t * scheduler  = NULL;

    scheduler  = SchedulerCreate();
    if (scheduler == NULL)
    {
        return NULL;
    }
    
    SetEnvWDPID();

    SchedulerCreate()
    
}

/******************************************************************************
*							STATIC FUNCTIONS 								  * 
******************************************************************************/


void SetEnvWDPID()
{
    char this_pid[20] =  NULL;
    sprintf("%d", getpid(), &this_pid);
    setenv("WD_pid", this_pid);
}