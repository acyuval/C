#ifndef __WATCHDOG_UTILS_H__
#define __WATCHDOG_UTILS_H__


pid_t GetEnvWDPID();

pid_t RunExe(char ** args);

void * SchedulerManager(void *params);

void SetEnvWDPID(pid_t pid);

int StopAll();

#endif /* __WATCHDOG_UTILS_H__ */
