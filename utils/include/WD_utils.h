#ifndef __WATCHDOG_UTILS_H__
#define __WATCHDOG_UTILS_H__

int SetSigActions();

pid_t GetEnvWDPID();

int SendSignalTask(void *);

int CheckAndReviveTask(void *);

int CheckFlagTask(void *);


pid_t RunExe(char ** args);

void * Scheduler_manager(void *params);

void SetEnvWDPID(pid_t pid);

int stop_all();

#endif /* __WATCHDOG_UTILS_H__ */
