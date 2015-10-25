#define _BSD_SOURCE
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int total_grade;
pthread_mutex_t mutex;

void *class_total(void *arg){

	int grade = (intptr_t)arg;
	usleep(10);
	pthread_mutex_lock (&mutex);
	total_grade += grade;
	pthread_mutex_unlock (&mutex);
	pthread_exit(NULL);
}

int main(void){

	pthread_t student_grades[10];
	pthread_mutex_init(&mutex, NULL);
	int  grade_in;

	printf("Please enter the student's grades:\n");

	for(int i = 0;i<9;i++){
		scanf("%d\n", &grade_in);
		pthread_create(&student_grades[grade_in], NULL, class_total, (void *)(intptr_t)grade_in);
		pthread_mutex_lock(&mutex);
		pthread_mutex_unlock(&mutex);
	  	pthread_join(student_grades[grade_in], 0);
	  	pthread_mutex_destroy(&mutex);
	}

	printf("The total grade is: %d\n", total_grade);
	pthread_exit(NULL);
	return(0);	
}
