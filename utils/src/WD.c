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
    printf("WATCHDOG START");

    if(argc == 1)
    {
        printf("agrc = 1");
    }

    status = Scheduler_manager(&argv[2]);
    if(status != NULL)
    {
        return FAIL;
    }

    return SUCCESS;
}

/******************************************************************************
*							STATIC FUNCTIONS 								  * 
******************************************************************************/
