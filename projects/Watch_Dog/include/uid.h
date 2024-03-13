#ifndef __UID_H__
#define __UID_H__

#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#define IP_SIZE (14)


typedef struct uid
{
    size_t counter;
    pid_t pid;
    time_t time;
    unsigned char ip [IP_SIZE];
}ilrd_uid_t;

extern const ilrd_uid_t bad_uid;


/******************************************************************************
*Description: Creates a new UID 
*Return Value: UID element 
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: Returns bad_uid if memory allocation fails.
******************************************************************************/
ilrd_uid_t UIDCreate(void);


/******************************************************************************
*Description: Compare two UID elements
*Parameters: Two diffrent UID to be compared 
*Return Value: 0 - not equal 
*              1 - equal
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
int UIDIsEqual(ilrd_uid_t uid1, ilrd_uid_t uid2); 

#endif	/* __UID_H__ */
