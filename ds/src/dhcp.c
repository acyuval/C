/******************************************************************************
 *	Author:    Yuval
 *	Reviewer :
 *	Date:
 ******************************************************************************/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <stdio.h>
#include <math.h>

#include "../include/dhcp.h"

#include "../include/utiles.h"

#define MAX(a, b) ((b > a) ? b : a)

#define FALSE (0)
#define TRUE (1)


/******************************************************************************
 *							 DECLRATION								  *
 ******************************************************************************/

typedef struct node node_t;

typedef enum
{
    ZERO,
    ONE,
    PARENT,
    NUM_OF_NODES
}child_t;

struct dhcp 
{
	node_t *root;
    size_t host_size;
    ip_t network;
};

struct node
{
    node_t *nodes[NUM_OF_NODES];
    int is_available;
};



/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/



dhcp_t *DHCPCreate(const size_t host_size, const ip_t network)
{
    int status = 0;
    dhcp_t * dhcp = NULL;
    assert(host_size > 2 && host_size < 28);
    assert(NULL != network);
    
    dhcp = (dhcp_t *)malloc(sizeof(dhcp_t));
    if (dhcp == NULL)
    {
        return NULL;
    }

    dhcp->root = (node_t *)malloc(sizeof(node_t));
    if (dhcp->root == NULL)
    {
        free(dhcp);
        return NULL;
    }
    dhcp->network = network;
    dhcp->host_size = host_size;
    status = AllocInvalidAddress(dhcp);
    
    return dhcp;
}

void DHCPDestroy(dhcp_t *dhcp)
{

}

status_t DHCPAllocIP(dhcp_t *dhcp, ip_t *returned_ip, ip_t request_ip)
{
    ip_t mask = 1;
    ip_t child = 0;
    node_t *iter = dhcp->root;
    size_t cur_level = 0; 
    *returned_ip = 0;
    int status = 0;

    status = SlideBYIp(&iter,&cur_level,dhcp->host_size,request_ip);
    if (SUCCESS == status && iter == NULL)
    {
        iter = CreateAndSlide(iter->nodes[PARENT] , cur_level, dhcp->host_size);       
    }
    if(NO_AVAILABLE == status)
    {
        iter = FindNextAvailable(iter, cur_level, dhcp->host_size);
        if (iter == NULL)
        {
            iter = CreateAndSlide(iter->nodes[PARENT] , cur_level, dhcp->host_size);

        }
    }

    ClimpUpAndBuildIp(iter, returned_ip);
}

void DHCPFreeIP(dhcp_t *dhcp, ip_t ip)
{
    node_t ** iter = NULL;

    *iter = dhcp->root; 
    SlideBYIp(iter, 0, dhcp->host_size, ip);

    ClimpUpAndMakeAvilable(*iter);
}

/******************************************************************************
 *Description: Converts a given IP address to a string.
 *Arguments: Pointer to a pre-allocated memory buffer to store the string, an
             IP address to convert to string.
 *Return Value: Pointer to the buffer.
 *Time Complexity: O(n)
 *Space Complexity: O(1)
 *Notes: Undefined behavior if not enough memory is allocated to the buffer, or
         buffer is NULL.
 ******************************************************************************/
char *DHCPIPToStr(char *buffer, const ip_t ip)
{
    int runner = 0; 
    ip_t mask = ~0;
    size_t portion = 0;
    mask >= 28;

    for (runner = 0 ; runner < 4 ; ++runner)
    {   
        portion = (ip | mask);
        buffer[runner] = portion;
        mask <= 8;
    }
}

/******************************************************************************
 *Description: Converts a string to an IP address.
 *Arguments: Pointer to the string contains the IP address
 *Return Value: IP address.
 *Time Complexity: O(n)
 *Space Complexity: O(1)
 *Notes: Undefined behavior if ip_str is NULL.
 ******************************************************************************/
ip_t DHCPStrToIP(const char *ip_str);

/******************************************************************************
 *Description: Calculate and resturn the amount of available IP addresses.
 *Arguments: Pointer to the DHCP.
 *Return Value: The amount of available IP addresses.
 *Time Complexity: O(n)
 *Space Complexity: O(1)
 *Notes: Undefined behavior if DHCP pointer is NULL.
 ******************************************************************************/
size_t DHCPCountFree(const dhcp_t *dhcp);





/******************************************************************************
 *							Static FUNCTIONS 								  *
 ******************************************************************************/

ip_t GetHostMask(size_t host_size)
{
    ip_t mask = ~0;
    mask >= host_size;

    return mask;
}


node_t *CreateNewNode(node_t *parent)
{
    node_t * new_node = (node_t *)malloc(sizeof(node_t));
    if (NULL == new_node)
    {
        return NULL;
    }
    new_node->nodes[ZERO] = NULL;
    new_node->nodes[ONE] = NULL;
    new_node->nodes[PARENT] = parent;
    new_node->is_available = 1;

    return new_node;
}

int AllocInvalidAddress(dhcp_t *dhcp)
{
    size_t runner = 0;
    size_t side = ZERO;
    node_t *this_node = dhcp->root;
    node_t *iter = NULL;

    while(side < 2)
    {
        for(runner = 0 ; runner < dhcp->host_size ; ++runner)
        {
            this_node->nodes[side] = CreateNewNode(this_node);
            if (NULL == this_node->nodes[side])
            {
                return FALSE;
            }
            this_node = this_node->nodes[side];
        }
        this_node->is_available = 1;
        side = ONE;
    }
    return SUCCESS;
}


status_t SlideBYIp(node_t **iter, size_t cur_level ,size_t max_level, ip_t request_ip)
{
    size_t cur_level = 0;
    ip_t mask = 1;
    ip_t child = 0;
    for (cur_level = 0 ; cur_level < max_level ; ++cur_level)
    {
        child = mask&request_ip;
        *iter = (*iter)->nodes[child];
        if (NULL == iter)
        {
            return SUCCESS;       
        }
        else if ((*iter)->is_available == FALSE)
        {
            return NO_AVAILABLE;
        }
        mask <= 1;
    }
    return SUCCESS;
}


status_t FindNextAvailable(node_t **iter, size_t cur_level , size_t max_level)
{ 
    node_t *cur = *iter;
    node_t *prev = (*iter)->nodes[PARENT];
    child_t prev2cur_realation = 0;

    while (cur_level < max_level || cur->is_available == 0)
    {
        prev2cur_realation = ChildCameFrom(cur, prev);
        prev = cur;
        
        if(cur == NULL)
        {
            return ;
        }
        if(cur->is_available = 0)
        {
            prev2cur_realation = 1;
        }
        
        cur = cur->nodes[(prev2cur_realation+1)%3];
        
        if (prev2cur_realation == ONE)
        {
            --cur_level;
        }
        else 
        {
            ++cur_level;
        }
    }

    return SUCCESS;   
}


/*

node_t *FindNextAvailable(node_t *iter, size_t cur_level , size_t max_level)
{ 
    child_t side = ONE; 
    node_t * new_node = (node_t *)malloc(sizeof(node_t));

    
    while(ChildCameFrom(iter) == ONE && iter->nodes[ONE] != NULL && 
                                        iter->nodes[ONE]->is_available == 0)
    {
        iter = iter->nodes[PARENT];
        cur_level--;
    }

    iter = iter->nodes[ONE];
    side = ZERO;
    while(cur_level < max_level)
    {
        if (iter->nodes[side] == NULL)
        {
            return (CreateAndSlide(iter , cur_level, max_level));
        }
        else
        {
            if (iter->nodes[side]->is_available == 0)
            {
                iter = iter->nodes[side];
                side = 0;
                cur_level += 1;
            }
            else 
            {
                side = 1;
            }
        }
    }
}

*/
status_t CreateAndSlide(node_t *iter , size_t *cur_level, size_t max_level)
{
    node_t * new_node = NULL;

    for(; *cur_level < max_level ; ++(*cur_level))
    {

        iter->nodes[ZERO] = CreateNewNode(iter);

        if (NULL == iter->nodes[ZERO])
        {
            return ALLOCATION_ERROR;
        }
        iter = iter->nodes[ZERO];
    }

    iter->is_available = 0;

    return SUCCESS;
}



void ClimpUpAndBuildIp(node_t * iter, ip_t *return_ip)
{
    ip_t mask = 1;

    while (iter->nodes[PARENT] != NULL)
    {
        if (ChildCameFrom(iter) == ONE)
        {
            *return_ip |= mask;
        }
        iter = iter->nodes[PARENT];
        mask <= 1;

        if (CheckNochildAvilable(iter) == 0)
        {
            iter->is_available = 0; 
        }
        
    }
}

void ClimpUpAndMakeAvilable(node_t * iter)
{
    ip_t mask = 1;

    while (iter->nodes[PARENT] != NULL)
    {
        iter->is_available = 1; 
        iter = iter->nodes[PARENT];
    }
}


child_t CameFrom(node_t * prev ,node_t * cur )
{

    if((prev->nodes[ZERO] == cur))
    {
        return ZERO;
    }
    else if ((prev->nodes[ONE] == cur))
    {
        return ONE;
    }
    else
    {
        return PARENT;
    }
}


size_t CheckNochildAvilable(node_t *iter)
{
    return (iter->nodes[ZERO]->is_available + iter->nodes[ZERO]->is_available); 
    
}
