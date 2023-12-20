/******************************************************************************
*	Author:    Yuval 
*	Reviewer : chen
*	Date:      
******************************************************************************/

#include <assert.h> /* assert			  */
#include <string.h> /* memcmp   		  */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ifaddrs.h>

#include "uid.h"

#define TRUE (1)
#define FALSE (0)
#define SUCCESS (0)
#define FAIL (-1)
/******************************************************************************
*							 DECLRATION								  * 
******************************************************************************/

const ilrd_uid_t bad_uid = {0};

static int GetIpInBuffer(unsigned char * ip_buffer);

/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/

int UIDIsEqual(ilrd_uid_t uid1, ilrd_uid_t uid2)
{
	int res =  (uid1.counter == uid2.counter) && (uid1.pid == uid2.pid) &&
					 			 SUCCESS == memcmp(uid1.ip, uid2.ip, IP_SIZE) &&
					 		 			( 0 == difftime(uid1.time, uid2.time));
	return res;
}


ilrd_uid_t UIDCreate(void)
{
	static int counter = 0;
	ilrd_uid_t uid = {0};
	
 	if(FAIL == GetIpInBuffer(uid.ip))
 	{
 		return bad_uid;
 	} 
 	
	uid.counter = ++counter;
	uid.pid = getpid();
	uid.time = time(NULL);
	if (FAIL == uid.time)
	{
		return bad_uid;
	}
	return uid;
}


/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/

static int GetIpInBuffer(unsigned char * ip_buffer)
{
	struct ifaddrs *ifap, *ifa;
    struct sockaddr_in *sa;
    int status = FAIL;
    getifaddrs (&ifap);
    
    for (ifa = ifap; ifa; ifa = ifa->ifa_next) 
    {
        if (ifa->ifa_addr && ifa->ifa_addr->sa_family==AF_INET) 
        {
            sa = (struct sockaddr_in *)ifa->ifa_addr;
            strcpy((char *)ip_buffer, inet_ntoa(sa->sin_addr));
            status = SUCCESS;
            break;
        }
    }
    
    freeifaddrs(ifap);
    return status;
}

