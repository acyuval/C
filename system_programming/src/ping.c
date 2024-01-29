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

int main(int argc , char ** argv)
{
	struct sigaction signal_sruct= {0};
	pid_t arg_pid = (pid_t)atoi(argv[1]);

	signal_sruct.sa_handler = SigHandler;
	
	sigaction(SIGUSR2, &signal_sruct, NULL);


	while(1)
	{
		kill(arg_pid, SIGUSR1);
		pause();
	}
	return 0;
}


void SigHandler()
{
	write(STDOUT_FILENO,"ping\n",5);
}
