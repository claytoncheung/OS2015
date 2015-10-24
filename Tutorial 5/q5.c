/*	Tutorial #5, Question #5
	Reads 10 grades from grades.txt using one thread with function read_grades()
	Use a barrier to wait for grades to be read
	Create 10 threads, each uses the function save_bellcurve(grade)
		adds grade to global var total_grade using +=
		bellcurves the grades by multiplying it by 1.50 and adds to global var total_bellcurve
		appends bellcurved grade to bellcurve.txt
		print total grade and class average before and after bellcurving 	*/
		
#include <stdio.h>
#include <pthread.h>
//Defines the number of grades and number of threads as constants
#define NUM_OF_GRADES 10;
#define NUM_OF_THREADS 10;


void *read_grades(void *arg){
	
	int *local_grades = (int *) arg;
	
	FILE *fp = fopen ("grades.txt", "r");
	
	for(i=0;i<NUM_OF_GRADES;i++)
		grades[i]=fscanf(fp, "%f", &grades[i]);
	
	int pthread_barrier_wait(&barrier);
	fclose(fp);
	pthread_exit(NULL);
}

void *save_bellcurve(void *arg) {
	int *local_grade = (int *) arg;
	//mutex
	total_grade += local_grade;
	total_bellcurve += (local_grade*1.5);
	fprintf(fp, "%f\n", (local_grade*1.5));
	
	
}

void main(int argc, char*argv[]) {
	
	//Creates arrays for grades and pthreads
	int grades[NUM_OF_GRADES]={0};
	pthread_t pth[NUM_OF_THREADS];
	int i, total_bellcurve, total_grade=0;
	
	//Initializes barrier object with count 1
	pthread_barrier_t barrier;
	int pthread_barrier_init(&barrier, NULL, 1);
	
	pthread_create(&pth[0], 0, read_grades, (void *) &grades);
	//Waiting for thread to complete
	pthread_barrier_wait (&barrier);
	
	FILE *fp = fopen ("bellcurve.txt", "a");
	
	for (i=0;i<NUM_OF_GRADES;i++) {
		pthread_create(&pth[i], 0, save_bellcurve, (void *) &grades[i]);
	}
	
	fclose(fp);
	
}