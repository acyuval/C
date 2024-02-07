/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/

#include <assert.h> /* assert			  */
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h> 
#include <stdatomic.h> 
#include <unistd.h>
#include "WD_utils.h"
#include "utils.h"
#include "WD.h"

/******************************************************************************
*							 DECLARATION								 		  * 
******************************************************************************/


/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/
int main(int argc, char ** argv)
{
    int * status = 0; 

    SetEnvWDPID(getpid());

    if(argc == 1)
    {
        write(1,"agrc = 1\n", 10);
    }

    status = SchedulerManager(argv[1]);
    if(status != NULL)
    {
        printf("WatchDog STOP\n");
        return FAIL;
    }
    return SUCCESS;
}

/******************************************************************************
*							STATIC FUNCTIONS 								  * 
******************************************************************************/
