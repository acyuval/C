#include <stdio.h>

#define Q_SIZE 64

struct Queue
{
	char m_queue[64];
	size_t m_elements_in_q;
	size_t m_first_element_index;
};


int QueuePushChar(struct Queue * q , char c)
{
	size_t index = 0 ; 
	
	if( q->m_elements_in_q == Q_SIZE)
	{
		return -1;
	}
	index= (q->m_elements_in_q + q->m_first_element_index) % Q_SIZE;
	(q->m_queue)[index] = c;
	q->m_elements_in_q += 1;
	return 1;
}

int QueuePopChar(struct Queue * q)
{
	size_t index = 0 ; 
	
	if( q->m_elements_in_q == 0)
	{
		return -1;
	}
	
	q->m_elements_in_q -= 1;
	q->m_first_element_index += 1;
}


int main() 
{
	struct Queue qu = {0};
	struct Queue *q = &qu;
	
	for (char i = 0 ; i< 64 ; i++) 
	{	
		QueuePushChar(q , 'a' + i);
	}
	
	printf("\n\nqueueu : %s \n", (qu.m_queue));
	
	printf("\n\nqueueu : %d \n",  QueuePushChar(q , 'a'));
  	
  	QueuePopChar(q);
  	
  	 printf("\n\nfull : %d \n",  QueuePushChar(q , 'a'));
    return 0;
}
