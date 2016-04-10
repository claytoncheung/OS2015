#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct grade {
	int student_id;
	int mark;
} grade;

void grade_students(grade *grades, int num_students);

int main(void)
{
	int i, num_students=0;
	char *professor = NULL;
	struct grade *grades = NULL;
	professor = (char *) calloc(256, sizeof(char));
	
	printf("Enter your name and the number of students to be marked: ");
	scanf("%s %d", professor, &num_students);
	grades =  (grade *)malloc(num_students * sizeof(*grades));

	for (i=0;i<num_students;i++)
	{
		printf("Enter the student ID followed by their mark: ");
		scanf("%d %d", &grades[i].student_id, &grades[i].mark);
	}
	
	grade_students(grades, num_students);
	free(professor);
	free(grades);
}

void grade_students(grade *grades, int num_students)
{
	FILE *fp = fopen("grades.txt", "w");
	int i,j,sum=0;
	double mean,sdev=0;
		
	for (i=0;i<num_students;i++)
	{
		sum += grades[i].mark;
		fprintf(fp, "%d %d \n", grades[i].student_id, grades[i].mark);
	}
	
	mean = (double) sum/num_students;
	
	for (j=0;j<num_students;j++)
	{
		sdev += pow((grades[j].mark - mean), 2);
	}
	sdev = sqrt(sdev/(double)num_students);
	fprintf(fp, "Mean: %f\nStandard Deviation: %f", mean, sdev);
	fclose(fp);
}