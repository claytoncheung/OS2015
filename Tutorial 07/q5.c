#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#define _GNU_SOURCE_

typedef struct proc{
	char name[20];
	int priority;
	int pid;
	int runtime;
} proc;

typedef struct queue{
	struct proc process;
	struct queue *next;
} queue_t;

int main (void) {
	//name, priority, runtime
	char* line = NULL;
	size_t len = 0;
	ssize_t read;
	struct queue *head, *current, *new_node = NULL;
	//head = malloc(sizeof(struct queue));
	current =  malloc(sizeof(struct queue));
	new_node =  malloc(sizeof(struct queue));


	FILE *fp = fopen("processes_q5.txt", "r");

	while ((read = getline(&line, &len, fp)) != -1) {
		//printf("%s", line);


		//tokenize, assign to proc
		strcpy(new_node->process.name, strtok(line, ","));

		new_node->process.priority = atoi(strtok(NULL, ","));

		new_node->process.runtime = atoi(strtok(NULL, "\n"));

		if (head == NULL){
			head = new_node;
			current = new_node;
		}
		else {
			current->next = new_node;
			current = new_node;
		}
	/*	printf("%s\n", current->process.name);
		printf("%d\n", current->process.priority);
		printf("%d\n", current->process.runtime);*/

	}
	current = head;
	for (int i = 0; i < 10; i ++){
		current = current->next;
	}
	fclose(fp);
}
