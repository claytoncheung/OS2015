#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#define NUM_STUDENTS 10

int total_grade;
pthread_mutex_t mutex;

void *class_total(void *arg){

	int *grade = (int *)arg;
	pthread_mutex_lock (&mutex);
	total_grade += *grade;
	pthread_mutex_unlock (&mutex);
	pthread_exit(NULL);
}

int main(void){

	pthread_t student_grades[NUM_STUDENTS];
	pthread_mutex_init(&mutex, NULL);
	int  grade[NUM_STUDENTS];
	int i=0;

	printf("Please enter the 10 student's grades :\n");
	
	for (i=0;i<NUM_STUDENTS;i++){
	    scanf("%d", &grade[i]);
	}

	for(i = 0;i<NUM_STUDENTS;i++)
		pthread_create(&student_grades[i], 0, class_total, (void *) &grade[i]);
	
	for (i=0;i<NUM_STUDENTS;i++)
	  	pthread_join(student_grades[i], NULL);

	printf("The total grade is: %d\n", total_grade);
	pthread_exit(NULL);
	return 0;	
}

