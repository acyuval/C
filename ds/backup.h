
typedef struct uid
{
    size_t counter;
    pid_t pid;
    time_t time;
    unsigned char ip [14];
}uid_t;

extern const uid_t bad_uid;


/******************************************************************************
*Description: Creates a new UID 
*Return Value: UID element 
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: Returns bad_uid if memory allocation fails.
******************************************************************************/
uid_t UIDCreate(void)


/******************************************************************************
*Description: Compare two UID elements
*Parameters: Two diffrent UID to be compared 
*Return Value: 0 - not equal 
*              1 - equal
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
int UIDIsEqual(uid_t , uid_t); 

