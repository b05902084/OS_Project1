#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "scheduling.h"

int main(){

	char policy[8];
	int N;
	struct process *proc;

	scanf("%s", policy);
	if (strcmp(policy, "SJF") != 0 && strcmp(policy, "PSJF") != 0 && strcmp(policy, "FIFO") != 0 && strcmp(policy, "RR") != 0){
		fprintf(stderr,"Invalid scheduling policy.");
		exit(1);
	}

	scanf("%d", &N);
	
	proc = (struct process *)malloc(N * sizeof(struct process));
	for (int i = 0; i < N; i++) {
		proc[i].pid = -1;
		scanf("%s", proc[i].name);
		scanf("%d", &proc[i].ready_time);
		scanf("%d", &proc[i].exec_time);
	}

	scheduling(policy, N, proc);
}
