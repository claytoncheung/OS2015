#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#define BUFFER_LEN 256

//............................................................................................
struct proc {
	char *name;
	int priority;
	int pid;
	int runtime;
};

//............................................................................................
typedef struct queue {
	struct proc process;
	struct queue *next;

} node_t;

//............................................................................................
void push(node_t *head, struct proc process){
	node_t *new_node;
	new_node = malloc(sizeof(node_t));

	new_node->process = process;
	new_node->next = head;
	head = new_node;
}

//............................................................................................
int pop(node_t *head){
	node_t *next_node = NULL;

	if (head == NULL){
		return -1;
	}

	next_node = head->next;
	free(head);
	head = next_node;

	return 0;
}

//...........................................................................................
int delete_name(node_t *head, char *name){
	node_t *current = head;
	node_t *temp_node = NULL;

	for(int i=0;i<10;i++){
		if (strcmp(name, current->process.name) == true){
			temp_node = current->next;
			current->next = temp_node->next;
			free(temp_node);
		}
		current = current->next;
	} 

	return 0;
}

//...........................................................................................
int delete_pid(node_t *head, int pid){
	node_t *current = head;
	node_t *temp_node = NULL;

	for(int i=0;i<10;i++){
		if(pid == current->process.pid){
			temp_node = current->next;
			current->next = temp_node->next;
			free(temp_node);
		}
		current = current->next;
	}

	return 0;
}

//............................................................................................
void print_list(node_t *head){
	node_t *current = head;

	while(current != NULL){
	printf("Name: %s 	Priority: %d 	PID: %d 	Runtime: %d\n", current->process.name, current->process.priority, current->process.pid, current->process.runtime);
	current = current->next;
}
}
//............................................................................................
int main(void) {
	

	FILE *fp = fopen("processes.txt", "r");
	const char s[2] = ",";
	char buffer[BUFFER_LEN] = { 0 };
	char *token;
	int j = 0;

	node_t *head = NULL;
	head = malloc(sizeof(node_t)); //Variable that points to the first item of the list

	if (head == NULL) {
		return 1;
	}

	struct proc process;

	for(int i=0;i<10;i++)
	{
		j -=1;
		if(j == -1){
			j = 0;
		}
		fgets(buffer, BUFFER_LEN, fp);
		token = strtok(buffer, s);
		
		if(j==0||j==4||j==8||j==12||j==16||j==20||j==24||j==28||j==32||j==36){
			head->process.name = token;
		}

		j += 1;
			while( token != NULL)
			{
				token = strtok(NULL, s);
				if(j==1||j==5||j==9||j==13||j==17||j==21||j==25||j==29||j==33||j==37){
					head->process.priority = atoi(token);	
				}
				if(j==2||j==6||j==10||j==14||j==18||j==22||j==26||j==30||j==34||j==38){
					head->process.pid = atoi(token);	
				}
				if(j==3||j==7||j==11||j==15||j==19||j==23||j==27||j==31||j==35||j==39){
					head->process.runtime = atoi(token);	
				}
				j++;
			}
			
		push(head, process);
		
	}

	print_list(head);

	printf("Which process would you like to delete?\n");
	char *in = NULL;
	in = (char *) calloc(BUFFER_LEN, sizeof(char));
	scanf("%s", in);
	delete_name(head, in);
	free(in);

	printf("Which process ID would you like to delete?\n");
	int del;
	scanf("%d", &del);
	delete_pid(head, del);
	
	print_list(head);

	for(int i=0;i<8;i++){
	pop(head);
	print_list(head);
	}

	fclose(fp);
	return 0;
}
