/******************************************************************************
 *	Author:    Yuval
 *	Reviewer : Dor
 *	Date:
 ******************************************************************************/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <stdio.h>
#include <math.h>
#include <arpa/inet.h>
#include "dhcp.h"
#include "utiles.h"



#define FALSE (0)
#define TRUE (1)
#define WITH_ALLOC (1)
#define NO_ALLOC (0)

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

ip_t GetHostMask(size_t host_size);
static node_t *CreateNewNode(node_t *parent);
static status_t AllocInvalidAddress(dhcp_t *dhcp);
static status_t SlideBYIp(node_t **iter ,size_t max_level, ip_t request_ip, int flag, ip_t *new_ip);
static void ClimpUpAndBuildIp(node_t * iter, ip_t *return_ip);
static void ClimpUpAndMakeAvilable(node_t * iter);
static child_t CameFrom(node_t * prev ,node_t * cur );
static size_t isChildsAvilable(node_t *iter);
static ip_t CalculateNewIP(size_t cur_level , size_t max_level, ip_t ip);

/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/



dhcp_t *DHCPCreate(const size_t host_size, const ip_t network)
{
    int status = 0;
    dhcp_t * dhcp = NULL;
    assert(host_size > 2 && host_size < 28);
    assert(0 != network);
    
    dhcp = (dhcp_t *)malloc(sizeof(dhcp_t));
    if (dhcp == NULL)
    {
        return NULL;
    }

    dhcp->root = CreateNewNode(NULL);
    if (dhcp->root == NULL)
    {
        free(dhcp);
        return NULL;
    }
    dhcp->network = network;
    dhcp->host_size = host_size;
    
    status = AllocInvalidAddress(dhcp);
    if (status == ALLOCATION_ERROR)
    {
        DHCPDestroy(dhcp);
        free(dhcp);
        return NULL;
    }
    
    return dhcp;
}

void DHCPDestroy(dhcp_t *dhcp)
{
    
    node_t *iter = dhcp->root;
    node_t *child = NULL;

    while(iter != NULL)
    {
        if(iter->nodes[ZERO] != NULL)
        {
            iter = iter->nodes[ZERO];
        }
        else if(iter->nodes[ONE] != NULL)
        {
            iter = iter->nodes[ONE];
        }
        else 
        {
            child = iter;
            iter = iter->nodes[PARENT];
            free(child);

            if (iter != NULL)
            {
                iter->nodes[CameFrom(iter, child)] = NULL;
            }
        }
    }
    free(dhcp);

}

status_t DHCPAllocIP(dhcp_t *dhcp, ip_t *returned_ip, ip_t request_ip)
{
    node_t *iter = NULL;
    size_t i = 0 ;
    ip_t first_request_ip = request_ip;
    ip_t *ip_ptr = &request_ip;
    status_t status = NO_AVAILABLE;
    ip_t mask = ~0;
    *returned_ip = 0;
    *ip_ptr = request_ip;
    
    if (FALSE == dhcp->root->is_available)
    {
        return NO_AVAILABLE;
    }

    while(status != SUCCESS)
    {
        iter = dhcp->root;
        status = SlideBYIp(&iter,dhcp->host_size,request_ip, WITH_ALLOC, ip_ptr);
        
        if (status == ALLOCATION_ERROR)
        {
            return ALLOCATION_ERROR;
        }
    }

    *returned_ip = request_ip; 
/*     mask = mask << dhcp->host_size;
    *returned_ip = request_ip & mask;  
    *returned_ip = *returned_ip >> dhcp->host_size;
     */
    ClimpUpAndBuildIp(iter, returned_ip);

    if(*returned_ip == request_ip)
    {
        return SUCCESS;
    }
    else
    {
        return NOT_REQUESTED;
    }
}

void DHCPFreeIP(dhcp_t *dhcp, ip_t ip)
{
    node_t * iter = NULL;

    iter = dhcp->root; 
    SlideBYIp(&iter,dhcp->host_size, ip, NO_ALLOC , NULL);

    ClimpUpAndMakeAvilable(iter);
}

char *DHCPIPToStr(char *buffer, const ip_t ip)
{
    int runner = 0; 
    unsigned char portion[4] = {0};
    ip_t mask = ip;
    for (runner = 0 ; runner < 4 ; ++runner)
    {   
        portion[runner] = (unsigned char)mask; 
        mask = mask >> 8;
    }
    sprintf(buffer, "%d.%d.%d.%d", portion[3],portion[2],portion[1],portion[0]);
    return buffer;
}

ip_t DHCPStrToIP(const char* ip_str) 
{
    struct in_addr ip_addr;  

    if (inet_pton(AF_INET, ip_str, &ip_addr) != 1)  
    {  
        return 0; 
    }  

    return ntohl(ip_addr.s_addr); 
}            

size_t DHCPCountFree(const dhcp_t *dhcp)
{

    child_t dir = ZERO;
    size_t level = dhcp->host_size -1 ;
    size_t counter = 0; 
    size_t max_ip = 1 << dhcp->host_size;   
    node_t *prev = dhcp->root;
    node_t *cur =prev->nodes[ZERO]; 

    while (cur->nodes[PARENT] != NULL || CameFrom(cur, prev) != ONE)
    {
        dir = CameFrom(cur, prev);
        if (cur->is_available == 0)
        {
            counter += (1 << level);
            dir = PARENT;
        }
        else
        {
            dir = (dir + 1) % 3;
            while(cur->nodes[dir] == NULL)
            {
                dir = (dir + 1) % 3; 
            }
        }

        (dir == PARENT) ? ++level: --level;
        prev = cur;
        cur = cur->nodes[dir];
    }
    return max_ip - counter;
}


/******************************************************************************
 *							Static FUNCTIONS 								  *
 ******************************************************************************/

static node_t *CreateNewNode(node_t *parent)
{
    node_t * new_node = (node_t *)malloc(sizeof(node_t));
    if (NULL == new_node)
    {
        return NULL;
    }
    new_node->nodes[ZERO] = NULL;
    new_node->nodes[ONE] = NULL;
    new_node->nodes[PARENT] = parent;
    new_node->is_available = TRUE;

    return new_node;
}

static status_t AllocInvalidAddress(dhcp_t *dhcp)
{
    ip_t all_zero = 0;
    ip_t all_one = ~0;
    ip_t buffer = 0;
    status_t status = 0;

    status = DHCPAllocIP(dhcp,&buffer, all_zero);
    if(status != SUCCESS)
    {
        return ALLOCATION_ERROR;
    }
    status = DHCPAllocIP(dhcp,&buffer, all_one);

    return status;
}

static status_t SlideBYIp(node_t **iter ,size_t max_level, ip_t request_ip, int flag, ip_t *ip_ptr)
{   
    ip_t mask = 1;
    child_t side = 0;
    size_t cur_level = 0;
    for (cur_level = 0 ; cur_level < max_level ; ++cur_level)
    {
        side = ((mask&request_ip) != 0)? ONE:ZERO;
        
        if(NULL == (*iter)->nodes[side])
        {
            (*iter)->nodes[side] = CreateNewNode(*iter);
            if (NULL == (*iter)->nodes[side])
            {
                return ALLOCATION_ERROR;
            }
        }
        else if((*iter)->nodes[side]->is_available == FALSE && flag == WITH_ALLOC)
        {
            *ip_ptr = CalculateNewIP(cur_level, max_level, request_ip);
            return NOT_REQUESTED;
        }

        mask <<= 1;
        (*iter) = (*iter)->nodes[side];
    }
    (*iter)->is_available = FALSE;

    return SUCCESS;
}


/* 
node_t *FindNextAvailable(node_t *iter, size_t max_level)
{ 
    child_t side = ONE; 
    node_t * new_node = (node_t *)malloc(sizeof(node_t));
    size_t cur_level = 0;
    
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

status_t CreateAndSlide(node_t *iter , size_t *cur_level, size_t max_level)
{

    for(; *cur_level < max_level-1 ; ++(*cur_level))
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
 */


static void ClimpUpAndBuildIp(node_t * iter, ip_t *return_ip)
{
    while (iter->nodes[PARENT] != NULL)
    {
/*         *return_ip = *return_ip << 1; 

        if (CameFrom(iter->nodes[PARENT] , iter) == ONE)
        {
            *return_ip |= 1;
        } */
        iter = iter->nodes[PARENT];

        if (isChildsAvilable(iter) == FALSE)
        {
            iter->is_available = FALSE; 
        }
    }
    
}


static ip_t CalculateNewIP(size_t cur_level , size_t max_level, ip_t ip)
{
    ip_t new_ip = ip;
    size_t net_bits = (sizeof(ip_t)- max_level);
    new_ip = new_ip >> cur_level;
    new_ip += 1 << cur_level;

    if (((new_ip << net_bits) >> net_bits) > ((ip_t)1 << max_level))
    {
        new_ip = (new_ip >> max_level) << max_level;
    }
    
    return new_ip;

}

static void ClimpUpAndMakeAvilable(node_t * iter)
{
    while (iter->nodes[PARENT] != NULL)
    {
        iter->is_available = 1; 
        iter = iter->nodes[PARENT];
    }
}

static child_t CameFrom(node_t * parent ,node_t * child )
{
    if((parent->nodes[ZERO] == child))
    {
        return ZERO;
    }
    else if ((parent->nodes[ONE] == child))
    {
        return ONE;
    }
    else
    {
        return PARENT;
    }
}

static size_t isChildsAvilable(node_t *iter)
{
    if (iter->nodes[ZERO] == NULL || iter->nodes[ONE] == NULL)
    {
        return TRUE;
    }
    else 
    {
        return (iter->nodes[ONE]->is_available || iter->nodes[ZERO]->is_available);  
    }
}


