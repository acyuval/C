/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
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

/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/



/******************************************************************************
*							STATIC FUNCTIONS 								  * 
******************************************************************************/
int SemaphoreInit(char *sem_name)
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

int SemOp(int sem_id ,int type ,int num, int flag_undo)
{
	struct sembuf sops = {0};
	
	num = (type == DECREMENT)? num * -1: num;  

	sops.sem_op = num;
	sops.sem_flg = (flag_undo == TRUE)? SEM_UNDO: 0;
	sops.sem_num = 0; 

	return semop(sem_id,&sops, 1); 
}


int GetVAl(int sem_id)
{
	return semctl(sem_id, 0, GETVAL); 
}





int sem_delete(int sem_id)
{
	union semun arg = {0};

	semctl(sem_id, 1, IPC_RMID, arg);
	return SUCCESS;
}



