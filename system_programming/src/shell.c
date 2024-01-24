/******************************************************************************
*	Author:    Yuval 
*	Reviewer : igal
*	Date:      
******************************************************************************/

#include <assert.h> /* assert			  */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define TRUE (1)
#define FALSE (0)
#define SUCCESS (0)
#define FAIL (-1)
/******************************************************************************
*							 DECLRATION								 		  * 
******************************************************************************/
int RunWithFork();
int RunWithSystem();
void ParseFlags(char *buffer, char **arg_list);
void ErrorHandle(int exit_status);
void GetCommand(char * buffer);

/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/

int main(int argc,char **argv)
{
	
	char *mode = argv[1];
	(void)argc;
	if(argc == 1)
	{
		printf("(choose system)/(fork)\n");
		return -1;
	}
	if(strcmp(mode, "fork") == SUCCESS)
	{
		printf("\nrun by fork\n");
		RunWithFork();

	}
	else if (strcmp(mode, "system") == SUCCESS)
	{
		printf("\nrun by system\n");
		RunWithSystem();
	}
	else 
	{
		printf("\ninvalid!\n");
		exit(1);
	}
	
	return 0;

}


/******************************************************************************
*							STATIC FUNCTIONS 								  * 
******************************************************************************/
int RunWithFork()
{
	char buffer[BUFSIZ] = {0};
	pid_t child_pid = 0;
	int child_status = 0;
	char *arg_list[30] = {NULL};
	
	while(1)
	{

		GetCommand(buffer);


		if(strcmp(buffer, "exit") == SUCCESS)
		{
			return SUCCESS;
		}
		else
		{
			child_pid = fork();
			if (child_pid > 0)  		/* parent block */
			{
				wait(&child_status);
				ErrorHandle(WEXITSTATUS(child_status));
			}
			else if (child_pid == 0)	/* child block */
			{	
				ParseFlags(buffer, arg_list);
				execvp(arg_list[0],arg_list);
				exit(FAIL);
			}
			else 
			{
				return(FAIL);
			}
		}
	}
	

}

void ParseFlags(char *buffer, char **arg_list)
{
	char *token = strtok(buffer," \n\t");
	while (token != NULL)
	{
		*arg_list = token;
		++arg_list;
		token = strtok(NULL," \n\t");
	}
}


void ErrorHandle(int exit_status)
{
	switch (exit_status)
	{
	case 0:
		printf("(exit normally!)\n");
		break;	
	case 255:
		printf("(couldnt run command)\n");
		break;	
	default:
		printf("(exit error code:%d)\n", exit_status);
		break;
	}
}


int RunWithSystem()
{
	char buffer[BUFSIZ] = {0};
	int status = 0;
	while(1)
	{
		GetCommand(buffer);
		if(strcmp(buffer, "exit") == SUCCESS)
		{
			exit(SUCCESS);
		}
		else
		{
			status = system(buffer);
			ErrorHandle(status);
		}
	}
	return SUCCESS;
}


void GetCommand(char * buffer)
{
	printf("\n<command> ");	
	fgets(buffer, BUFSIZ , stdin);
	buffer[strcspn(buffer,"\n")] = '\0';
}