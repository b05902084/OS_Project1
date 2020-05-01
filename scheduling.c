#define _GNU_SOURCE
#include "scheduling.h"
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <time.h>

#define PRINTKERNEL 333
#define GETTIME 334

char policy[8];
int N;
struct process *process;

int timer = 0;
int current = -1;
int finish_process = 0;
int lastcs_time = 0;

void get_time(unsigned long *t1,unsigned long *t2){
	t1=0;
	t2=0;
}

int compare(const void *p1, const void *p2) {
	return ((struct process *)p1)->ready_time - ((struct process *)p2)->ready_time;
}

void assign(int pid, int core)
{
	if (core > sizeof(cpu_set_t)) {
		fprintf(stderr, "Invalid core.");
		exit(2);
	}

	cpu_set_t mask;
	CPU_ZERO(&mask);
	CPU_SET(core, &mask);
	size_t mask_size = sizeof(mask);

	if (sched_setaffinity(pid, mask_size, &mask) < 0){
		perror("Error on sched_setaffinity");
		exit(3);
	}
}

int exec(struct process process)
{
	int pid = fork();

	if (pid < 0) {
		perror("Error on fork");
		return -1;
	}

	if (pid == 0) {
		struct timespec start_time, finish_time;
		syscall(GETTIME, &start_time.tv_sec, &start_time.tv_nsec);
		for (int i = 0; i < process.exec_time; i++) {
			TICKTOCK();
		}
		syscall(GETTIME, &finish_time.tv_sec, &finish_time.tv_nsec);
		char buf[200];
		const char tag[11] = "[Project1]";
		sprintf(buf, "%s %d %lu.%09lu %lu.%09lu", tag, getpid(), start_time.tv_sec, start_time.tv_nsec, finish_time.tv_sec, finish_time.tv_nsec);
		syscall(PRINTKERNEL, buf, 200);
		exit(0);
	}
	assign(pid, CHILD);

	return pid;
}

void set_priority(int pid, int priority)
{
	struct sched_param sp;
	sp.sched_priority = 0;

	if (sched_setscheduler(pid, priority, &sp) < 0){
		perror("Error on sched_setscheduler");
		exit(4);
	}
}

int find_next(){
	if (strcmp(policy, "FIFO") == 0){
		if (current != -1) return current;

		else
			for (int i = 0; i < N; i++)
				if (process[i].pid != -1 && process[i].exec_time > 0)
					return i;
	}

	else if (strcmp(policy, "RR") == 0){
		if (current != -1){
			if ((timer - lastcs_time) % TIME_QUANTUM == 0){
				for (int i = current; i < current + N ; i++)
					if (process[i%N].pid != -1 && process[i%N].exec_time > 0)
						return i;
			}
			else return current;
		}
		else
			for (int i = 0; i < N; i++)
				if (process[i].pid != -1 && process[i].exec_time > 0)
					return i;
	}

	else if (strcmp(policy, "SJF") == 0){
		if (current != -1) return current;

		else{
			int min = -1;
			for (int i = 0; i < N; i++)
				if (process[i].pid != -1 && process[i].exec_time > 0)
					if (min == -1 || process[i].exec_time < process[min].exec_time)
						min = i;
			return min;
		}
	}
	else if (strcmp(policy, "PSJF") == 0){		
		int min = -1;
		for (int i = 0; i < N; i++)
			if (process[i].pid != -1 && process[i].exec_time > 0)
				if (min == -1 || process[i].exec_time < process[min].exec_time)
					min = i;
		return min;
	}

	else{
		fprintf(stderr, "Invalid scheduling policy");
		exit(5);
	}

	return -1;
}

void context_switch(int next){
	set_priority(process[next].pid,SCHED_OTHER);
	set_priority(process[current].pid,SCHED_IDLE);
	current = next;
	lastcs_time = timer;
}

int scheduling(char* p, int n, struct process *proc){
	strcpy(policy,p);
	N = n;
	process = (struct process *)malloc(N * sizeof(struct process));
	for (int i = 0 ; i < N ; i++){
		process[i] = proc[i];
	}

	qsort(process, N, sizeof(struct process), compare);

	assign(getpid(), PARENT);
	
	set_priority(getpid(), SCHED_OTHER);
	
	while(finish_process < N) {

		if (current != -1 && process[current].exec_time == 0) {
			waitpid(process[current].pid, NULL, 0);
			printf("%s %d\n", process[current].name, process[current].pid);
			current = -1;
			finish_process++;
		}

		for (int i = 0; i < N; i++) 
			if (process[i].ready_time == timer) {
				process[i].pid = exec(process[i]);
				set_priority(process[i].pid, SCHED_IDLE);
			}

		int next = find_next();
		if (next != -1 || next != current)
			context_switch(next);

		TICKTOCK();
		if (current != -1)
			process[current].exec_time--;
		timer++;
	}

	return 0;
}
