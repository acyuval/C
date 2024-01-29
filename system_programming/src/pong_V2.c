/******************************************************************************
*	Author:    Yuval 
*	Reviewer : igal
*	Date:      
******************************************************************************/
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


	child_pid = fork();
	if (child_pid > 0)  		/* parent block */
	{
		while(1)
		{
			kill(child_pid, SIGUSR1);
			sleep(1);
		}
		wait(&child_status);
	}
	else if (child_pid == 0)	/* child block */
	{	
		execvp("./pong.exe", NULL);
	}
	return 0;
}


void SigHandler()
{
	write(STDOUT_FILENO,"pong\n",5);
}