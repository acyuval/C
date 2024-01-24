/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/
#define _POSIX_C_SOURCE 199309L
#define _POSIX_SOURCE
#include <assert.h> /* assert			  */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <unistd.h>
#include <signal.h>


#define TRUE (1)
#define FALSE (0)
#define SUCCESS (0)
#define FAIL (-1)
/******************************************************************************
*							 DECLRATION								 		  * 
******************************************************************************/

void SigHandler();
int pong();
/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/
volatile sig_atomic_t sender_pid = -1;


int main()
{
	pong();
	return 0;

}



/******************************************************************************
*							STATIC FUNCTIONS 								  * 
******************************************************************************/
int pong()
{
	pid_t child_pid = 0;
	int child_status = 0;
	
	struct sigaction singal= {0};
	singal.sa_handler = SigHandler;
	sigaction(SIGUSR1, &singal, NULL);

	while(1)
	{
		printf("1:%d", sender_pid);
		kill(sender_pid, SIGUSR1);
	}

	return 0;
}



void SigHandler(int sig, siginfo_t *info, void *context)
{
	sender_pid = info->si_pid;
	write(STDOUT_FILENO,"pong\n",5);
}