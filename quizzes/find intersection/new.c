#include <stdio.h>
#include "../../ds/include/sll_exer.h"
#define ROWS 8
#define COLS 8


node_t * FindIntersection(node_t *node_1 ,node_t *node_2)
{
	node_t * itrA = node_1;
	node_t * itrB = node_2;
	long counter = 0; 
	
	while(itrA->next != NULL)
	{
		itrA = itrA->next;
		counter++;
	}
	
	while(itrB != NULL)
	{
		itrB = itrB->next;
		counter--;
	}

	if(itrA == itrB)
	{
		node_t * itrA = node_1;
		node_t * itrB = node_2;
		if(counter > 0)
		{
			while(0 != counter--)
			{
				itrA = itrA->next;
			}
		}
		
		if(counter < 0)
		{
			while(0 != counter++)
			{
				itrB = itrB->next;
			}
		}
		
		while(itrA != itrB)
		{
			itrA = itrA->next;
			itrB = itrB->next;
		}	
		
		return itrA;	
	}	
	
	return NULL;
}

void seperate(node_t * iterA, node_t * iterB)
{
    node_t * intersec = FindIntersection(iterA,iterB);

	while(iterA->next != intersec)
	{
		iterA = iterA->next;
	}	
	iterA->next = NULL;
}

int main() {
  
    return 0;
}
