#ifndef _SCHEDULING_H_
#define _SCHEDULING_H_

#include <sys/types.h>

#define CHILD 1
#define PARENT 0

#define TIME_QUANTUM 500

#define TICKTOCK() {volatile unsigned long i; for (i = 0; i < 1000000UL; i++);}						\

struct process {
	pid_t pid;
	char name[32];
	int ready_time;
	int exec_time;
};

int scheduling(char* policy, int N, struct process *process);

#endif
