#ifndef __WATCHDOG_UTILS_H__
#define __WATCHDOG_UTILS_H__

int SetSigActions();

pid_t GetEnvWDPID();

int SendSignalTask(void *);

int CheckAndReviveTask(void *);

int CheckFlagTask(void *);

void SignalHandler1();

pid_t RunExe(char ** args);

void SignalHandler2();

void * Scheduler_manager(void *params);



int stop_all();

#endif /* __WATCHDOG_UTILS_H__ */
