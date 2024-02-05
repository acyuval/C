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
#include <sys/ipc.h>
#include <sys/sem.h>
#include <ctype.h>

#define TRUE (1)
#define FALSE (0)
#define SUCCESS (0)
#define FAIL (-1)
#define INCREMENT (1)
#define DECREMENT (-1)
/******************************************************************************
*							 DECLRATION								 		  * 
******************************************************************************/
union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
	struct seminfo *__buf;
};

static int SemaphoreInit(char *sem_name);
static int SemOp(int type , int sem_id , char * buffer);
static int GetVAl(int sem_id);
static int GetNumFromBuffer(char * buffer);
static int isUndo(char *buffer);
/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/

int main(int argc,char **argv)
{
	char command = 0; 
	int sem_id = 0; 
	int status = 0;
	char *sem_name = argv[1];
	char buffer[BUFSIZ] = {0}; 
	if(argc == 1)
	{
		printf("(missing semaphore name)\n");
		return FAIL;
	}
	else
	{
		sem_id = SemaphoreInit(sem_name);

		while(status == SUCCESS)
		{
			fgets(buffer, BUFSIZ, stdin);

			command = buffer[0];
		
			switch (command)
			{
			case 'D': 
				status = SemOp(sem_id, DECREMENT , buffer);
				break;
			case 'I':
				status = SemOp(sem_id, INCREMENT, buffer);
				break;
			case 'V':
				printf("value of semaphore is %d\n" , GetVAl(sem_id));
				break;
			case 'X':
				return SUCCESS;
			default:
				break;
			}
		}
	}

	return status;
}


/******************************************************************************
*							STATIC FUNCTIONS 								  * 
******************************************************************************/
static int SemaphoreInit(char *sem_name)
{
	FILE * file = NULL;
	int sem_id = 0;
	key_t key = 0;
	int status = 0;
	char path[BUFSIZ] = {0};
	union semun argument = {0};
	unsigned short values[1];

	strcat(path , "./semaphors/");
	strcat(path ,sem_name);

	file = fopen(path, "a");
	if (file == NULL)
	{
		return FAIL;
	}
	fclose(file);
	
	key = ftok(path, 2024);
	
	sem_id = semget(key, 1, IPC_EXCL | IPC_CREAT |0666);

	if (sem_id == -1)
	{
		return semget(key, 1, 0666);
	}
 
	values[0] = 0;
	argument.array = values;
	status = semctl(sem_id, 0, SETALL, argument);
	if(status == FAIL)
	{
		return FAIL;
	}
	
	return sem_id;
}

static int SemOp(int sem_id ,int type ,char * buffer)
{
	int num = 0; 
	struct sembuf sops = {0};
	
	num = GetNumFromBuffer(buffer);

	num = (type == DECREMENT)? num * -1: num;  

	sops.sem_op = num;
	sops.sem_flg = (isUndo(buffer) == TRUE)? SEM_UNDO: 0;
	sops.sem_num = 0; 

	return semop(sem_id,&sops, 1); 
}


static int GetVAl(int sem_id)
{
	return semctl(sem_id, 0, GETVAL); 
}

static int GetNumFromBuffer(char * buffer)
{
	return atoi(buffer+1);
}


static int isUndo(char *buffer)
{
	return (strstr(buffer, "[undo]") != NULL);
}


