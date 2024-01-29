/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/
#define _POSIX_C_SOURCE 199309L
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
	
	singal.sa_flags = SA_SIGINFO;
	singal.sa_sigaction = SigHandler;
	
	sigaction(SIGUSR1, &singal, NULL);
	
	while(1)
	{
		printf("\n1:%d\n", sender_pid);
		pause();
		kill(sender_pid, SIGUSR2);
	}

	return 0;
}



void SigHandler(int sig, siginfo_t *info, void *context)
{
	sender_pid = info->si_pid;
	write(STDOUT_FILENO,"pong\n",5);
}