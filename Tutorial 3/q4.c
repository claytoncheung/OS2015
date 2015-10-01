#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	char *professor = NULL;
	int *student_ids = NULL;
	int *grades = NULL;
	int num_of_students=0;
	
	professor = (char *) calloc(256, sizeof(char));
	printf("Please enter your name and the number of students to mark: ");
	scanf("%s %d", professor, &num_of_students);

	student_ids = (int *) malloc(num_of_students * sizeof(int));
	grades = (int *) malloc(num_of_students * sizeof(int));
	
	free(professor);
	free(student_ids);
	free(grades);
}