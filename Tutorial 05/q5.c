/*	Tutorial #5, Question #5
	Reads 10 grades from grades.txt using one thread with function read_grades()
	Use a barrier to wait for grades to be read
	Create 10 threads, each uses the function save_bellcurve(grade)
	adds grade to global var total_grade using +=
	bellcurves the grades by multiplying it by 1.50 and adds to global var total_bellcurve
	appends bellcurved grade to bellcurve.txt
	print total grade and class average before and after bellcurving 			*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "q5.h"
//barrier variable
pthread_barrier_t barrier;
//mutex variable
pthread_mutex_t mutex;

void *readGrades(void *arg){
	
	allGrades *g = (allGrades *) arg;
	
	FILE *fp = fopen ("grades.txt", "r");
	
	for(int i=0;i<NUM_OF_GRADES;i++)
		fscanf(fp, "%f", &g->grades[i]);
	
	pthread_barrier_wait(&barrier);
	fclose(fp);
	pthread_exit(NULL);
}

void *bellcurve(void *arg) {
	FILE *fp = fopen ("bellcurve.txt", "a");
	allGrades *g = (allGrades *) arg;
	//Request mutex lock
	pthread_mutex_lock(&mutex);
	
	g->total_grade += g->grades[g->counter];
	g->total_bellcurve += (g->grades[g->counter]*1.5);
	fprintf(fp, "%f\n", (g->grades[g->counter]*1.5));
	g->counter++;
	//Release mutex lock
	pthread_mutex_unlock(&mutex);

	fclose(fp);
	pthread_exit(NULL);
}

int main() {
	
	//initializes struct
	allGrades grade;
	grade.total_bellcurve=0;
	grade.total_grade=0;
	grade.counter=0;
	
	//Creates arrays for grades and pthreads
	pthread_t pth[NUM_OF_THREADS];
	int i=0;
	
	//Initializes barrier object with count 1
	pthread_barrier_init(&barrier, NULL, 1);
	
	
	pthread_create(&pth[0], 0, readGrades, (void *) &grade.grades);
	//Waiting for thread to complete before continuing
	//pthread_barrier_wait (&barrier);
	pthread_join(pth[0], NULL);
	//Initialize the mutex
	pthread_mutex_init(&mutex, NULL);
	
	//Bellcurving the grades
	for (i=0;i<NUM_OF_THREADS;i++) {
		pthread_create(&pth[i], 0, bellcurve, (void *) &grade);
	}
	//pthread_join
	for (i=0;i<NUM_OF_THREADS;i++){
		pthread_join(pth[i], NULL);
	}
	//print before and after totals
	printf("The class total was %f\n", grade.total_grade);
	printf("The class total after the bellcurve is %f\n", grade.total_bellcurve);
	
	//Destroy the mutex
	pthread_mutex_destroy(&mutex);
	
	pthread_exit(NULL);
	return 0;
}
