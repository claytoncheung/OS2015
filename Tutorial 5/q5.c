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
#include <unistd.h>
//Defines the number of grades and number of threads as constants
#define NUM_OF_GRADES 10;
#define NUM_OF_THREADS 10;
//barrier variable
pthread_barrier_t barrier;
//mutex variable
pthread_mutex_t mutex;


void *readGrades(void *arg){
	
	float *localGrade = (float *) arg;
	
	FILE *fp = fopen ("grades.txt", "r");
	
	for(i=0;i<NUM_OF_GRADES;i++)
		grades[i]=fscanf(fp, "%f", &grades[i]);
	
	int rc = pthread_barrier_wait(&barrier);
	fclose(fp);
	pthread_exit(NULL);
}

void *bellcurve(void *arg) {
	float *localGrades = (float *) arg;
	//Request mutex lock
	pthread_mutex_lock(&mutex);
	
	total_grade += local_grade;
	total_bellcurve += (local_grade*1.5);
	
	//Release mutex lock
	pthread_mutex_unlock(&mutex);
	
	fprintf(fp, "%f\n", (local_grade*1.5));	
	pthread_exit(NULL);
}

void main(int argc, char*argv[]) {
	
	//Creates arrays for grades and pthreads
	float grades[NUM_OF_GRADES]={0};
	pthread_t pth[NUM_OF_THREADS];
	float total_bellcurve, total_grade=0;
	int i;
	
	//Initializes barrier object with count 1
	pthread_barrier_init(&barrier, NULL, 1);
	
	
	pthread_create(&pth[0], 0, readGrades, (void *) &grades);
	//Waiting for thread to complete before continuing
	pthread_barrier_wait (&barrier);
	
	//Initialize the mutex
	pthread_mutex_init(&mutex, NULL);
	
	//Bellcurving the grades
	FILE *fp = fopen ("bellcurve.txt", "a");
	for (i=0;i<NUM_OF_GRADES;i++) {
		pthread_create(&pth[i], 0, bellcurve, (void *) &grades[i]);
	}
	//pthread_join
	for (i=0;i<NUM_OF_THREADS;i++){
		pthread_join(pth[i], NULL);
	}
	//print before and after totals
		printf("The class average was %f", total_grade/NUM_OF_GRADES);
	printf("The class average after the bellcurve is %f", total_bellcurve/NUM_OF_GRADES);
	//Destroy the mutex
	pthread_mutex_destroy(&mutex);
	
	fclose(fp);
	pthread_exit(NULL);
}