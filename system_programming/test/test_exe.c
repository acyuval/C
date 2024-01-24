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

#include <time.h>

void SigHandler();

int main()
{
    time_t timer = 0;
    int num_of_sec = 5;

	struct sigaction singal= {0};
	singal.sa_handler = SigHandler;
	sigaction(SIGUSR1, &singal, NULL);
    
    while (1)
    {
        printf("time is %ld\n", time(NULL));
        sleep(10);
        timer++;
        kill(getppid(), SIGUSR1);
    }

    return 0;
}

void SigHandler()
{
	write(STDOUT_FILENO,"ping\n",5);
}
