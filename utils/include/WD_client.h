#ifndef __WATCHDOG_CLIENT_H__
#define __WATCHDOG_CLIENT_H__

/* in source file

    #include "scheduler.h"
    

*/

/******************************************************************************
 *Description: Start a watchdog process.
 *Arguments: The path to the user executable.
 *Return Value: 
 *Notes: if a user process run this function when there is already an existing
 *       watchdog, it doesn't create another one
 ******************************************************************************/
int WatchdogStart(char **args);


/******************************************************************************
 *Description: Stop a watchdog process.
 *Arguments: 
 *Return Value: 
 *Notes:    
 ******************************************************************************/
void WatchdogStop();



#endif /* __WATCHDOG_CLIENT_H__ */

