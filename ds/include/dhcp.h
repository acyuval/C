#ifndef __DHCP_H__
#define __DHCP_H__

#include <stddef.h> /*  size_t  */
#include <stdint.h> /*  uint32_t    */

typedef struct dhcp dhcp_t;
typedef uint32_t ip_t;


typedef enum
{
    SUCCESS = 0,
    NO_AVAILABLE,
    NOT_REQUESTED,
    ALLOCATION_ERROR
} status_t;


/******************************************************************************
 *Description: Creates a new DHCP.
 *Arguments: host_size - Define the amount of bits dedicated to the host (2 - 28)
             network - The network IP.
 *Return Value: Pointer to the created DHCP. NULL if allocation failed.
 *Time Complexity: O(1)
 *Space Complexity: O(1)
 *Notes: Returns NULL if memory allocation fails.
 *       Undefined behavior if host_size < 2 or host_size > 28.
 *       Undefined behavoir if given network IP is not aligned with the host
 *       size.
 ******************************************************************************/
dhcp_t *DHCPCreate(const size_t host_size, const ip_t network);

/******************************************************************************
 *Description: Destroys the DHCP.
 *Arguments: Pointer to the DHCP.
 *Return Value: None.
 *Time Complexity: O(n)
 *Space Complexity: O(1)
 *Notes: None.
 ******************************************************************************/
void DHCPDestroy(dhcp_t *dhcp);

/******************************************************************************
 *Description: Allocate an IP address as requested or free IP address
 *Arguments: Pointer to the dhcp, pointer to the returned IP, a requested IP.
 *Return Value: SUCCESS if allocation was successful.
                NO_AVAILABLE if there's no available IP address.
                NOT REQUESTED if requested IP was not available or found, but
                another IP address was allocated.
                ALLOCATION_ERROR if memory allocation failed.
 *Time Complexity: O(log n)
 *Space Complexity: O(1)
 *Notes: Undefined behavior if DHCP pointer is NULL.
         Undefined behavior if the requested IP is not a valid address.
 ******************************************************************************/
status_t DHCPAllocIP(dhcp_t *dhcp, ip_t *returned_ip, ip_t request_ip);

/******************************************************************************
 *Description: Deallocate the given IP address.
 *Arguments: Pointer to the DHCP, an IP address te free.
 *Return Value: None.
 *Time Complexity: O(log n)
 *Space Complexity: O(1)
 *Notes: Undefined behavior if DHCP is NULL.
         Undefined behavior if the given IP address is not valid.
 ******************************************************************************/
void DHCPFreeIP(dhcp_t *dhcp, ip_t ip);

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
char *DHCPIPToStr(char *buffer, const ip_t ip);

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

#endif /* __DHCP_H__ */
