#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__


int sem_delete(int sem_id);

int GetVAl(int sem_id);

int SemOp(int sem_id ,int type ,int num, int flag_undo);

int SemaphoreInit(char *sem_name);

#endif /* __SEMAPHORE_H__ */
