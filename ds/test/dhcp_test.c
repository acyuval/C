#include <stdio.h>
#include <string.h>

#include "../include/dhcp.h"

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


void TestDHCPCreate();
void TestDHCPAllocIP();
void TestDHCPStrToIP();
void TestDHCPIPToStr();
void TestDHCPFreeIP();
void TestDHCPCountFree();


int main()
{
    TestDHCPCreate();

    TestDHCPAllocIP();
    TestDHCPFreeIP();
    TestDHCPIPToStr();
    TestDHCPStrToIP();
    TestDHCPCountFree();
    return (0);
}

void Test(int check)
{
	if (0 == check)
	{
		printf("--------failure\n");
	}
	
	else
	{
		printf("success\n");
	}
}

void TestDHCPCreate()
{
    dhcp_t *dhcp = DHCPCreate(8, DHCPStrToIP("192.2.2.34"));
    size_t i = 0;
    node_t *runner = dhcp->root;

    printf("\ntesting Create\n");

    Test(dhcp->host_size == 8);

    for (i = 0; i < 8; ++i)
    {
        runner = runner->nodes[ZERO];
    }

    Test(0 == runner->is_available);

    runner = dhcp->root;
    for (i = 0; i < 8; ++i)
    {
        runner = runner->nodes[ONE];
    }

    Test(0 == runner->is_available);

    DHCPDestroy(dhcp);
}

void TestDHCPAllocIP()
{
    dhcp_t *dhcp = DHCPCreate(8, DHCPStrToIP("192.2.2.34"));
    status_t status = 0;
    ip_t result = 0;
    char buffer[16] = {0};

    printf("\ntesting AllocIP\n");

    status = DHCPAllocIP(dhcp, &result, DHCPStrToIP("192.2.2.12"));
    Test(SUCCESS == status);
    Test(0 == strcmp("192.2.2.12", DHCPIPToStr(buffer, result)));

    status = DHCPAllocIP(dhcp, &result, DHCPStrToIP("192.2.2.12"));
    Test(NOT_REQUESTED == status);
    Test(0 == strcmp("192.2.2.13", DHCPIPToStr(buffer, result)));

    status = DHCPAllocIP(dhcp, &result, DHCPStrToIP("192.2.2.12"));
    Test(NOT_REQUESTED == status);
    Test(0 == strcmp("192.2.2.14", DHCPIPToStr(buffer, result)));

    status = DHCPAllocIP(dhcp, &result, DHCPStrToIP("192.2.2.255"));
    Test(NOT_REQUESTED == status);
    Test(0 == strcmp("192.2.2.1", DHCPIPToStr(buffer, result)));

    status = DHCPAllocIP(dhcp, &result, DHCPStrToIP("192.2.2.254"));
    Test(SUCCESS == status);
    Test(0 == strcmp("192.2.2.254", DHCPIPToStr(buffer, result)));

    status = DHCPAllocIP(dhcp, &result, DHCPStrToIP("192.2.2.0"));
    Test(NOT_REQUESTED == status);
    Test(0 == strcmp("192.2.2.2", DHCPIPToStr(buffer, result)));

    status = DHCPAllocIP(dhcp, &result, DHCPStrToIP("192.2.2.254"));
    Test(NOT_REQUESTED == status);
    Test(0 == strcmp("192.2.2.3", DHCPIPToStr(buffer, result)));

    DHCPDestroy(dhcp);
}

void TestDHCPFreeIP()
{
    dhcp_t *dhcp = DHCPCreate(8, DHCPStrToIP("192.2.2.34"));
    ip_t result = 0;
    char buffer[16] = {0};

    printf("\ntesting FreeIP\n");

    DHCPAllocIP(dhcp, &result, DHCPStrToIP("192.2.2.12"));
    DHCPAllocIP(dhcp, &result, DHCPStrToIP("192.2.2.12"));
    DHCPAllocIP(dhcp, &result, DHCPStrToIP("192.2.2.12"));

    DHCPFreeIP(dhcp, DHCPStrToIP("192.2.2.13"));

    Test(NOT_REQUESTED == DHCPAllocIP(dhcp, &result, DHCPStrToIP("192.2.2.12")));
    Test(0 == strcmp("192.2.2.13", DHCPIPToStr(buffer, result)));
    Test(NOT_REQUESTED == DHCPAllocIP(dhcp, &result, DHCPStrToIP("192.2.2.12")));
    Test(0 == strcmp("192.2.2.15", DHCPIPToStr(buffer, result)));

    DHCPFreeIP(dhcp, DHCPStrToIP("192.2.2.12"));

    Test(SUCCESS == DHCPAllocIP(dhcp, &result, DHCPStrToIP("192.2.2.12")));
    Test(0 == strcmp("192.2.2.12", DHCPIPToStr(buffer, result)));

    DHCPDestroy(dhcp);   
}

void TestDHCPIPToStr()
{
    ip_t ip_addr1 = 3221357090;
    ip_t ip_addr2 = 2585362217;

    char ip1[16] = {0};
    char ip2[20] = {0};

    printf("\ntesting IPToStr\n");

    DHCPIPToStr(ip1, ip_addr1);
    DHCPIPToStr(ip2, ip_addr2);

    Test(0 == strcmp(ip1, "192.2.2.34"));
    Test(0 == strcmp(ip2, "154.25.127.41"));
}

void TestDHCPStrToIP()
{
    char ip1[] = "192.2.2.34";
    char ip2[] = "154.25.127.41";

    ip_t ip_addr1 = 0;
    ip_t ip_addr2 = 0;

    printf("\ntesting StrToIP\n");
    
    ip_addr1 = DHCPStrToIP(ip1);
    ip_addr2 = DHCPStrToIP(ip2);

    Test(3221357090 == ip_addr1);
    Test(2585362217 == ip_addr2);

}

void TestDHCPCountFree()
{
    dhcp_t *dhcp = DHCPCreate(4, DHCPStrToIP("192.2.2.64"));
    ip_t result = 0;
    size_t i = 0;

    printf("\ntesting CountFree\n");

    Test(14 == DHCPCountFree(dhcp));

    for (i = 0; i < 10; ++i)
    {
        DHCPAllocIP(dhcp, &result, DHCPStrToIP("192.2.2.64") + i);
    }

    Test(4 == DHCPCountFree(dhcp));

    DHCPFreeIP(dhcp, DHCPStrToIP("192.2.2.66"));
    DHCPFreeIP(dhcp, DHCPStrToIP("192.2.2.70"));

    Test(6 == DHCPCountFree(dhcp));

    DHCPDestroy(dhcp);

printf("\n");
}