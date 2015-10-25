#ifndef Q5_H_
#define Q5_H_

//Defines the number of grades and number of threads as constants
#define NUM_OF_GRADES 10
#define NUM_OF_THREADS 10

typedef struct {
	float grades[NUM_OF_GRADES];
	float total_grade;
	float total_bellcurve;
	int counter;
} allGrades;

#endif 
//Q5_H_
