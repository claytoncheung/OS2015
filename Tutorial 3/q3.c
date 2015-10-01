#include <stdlib.h>
#include <stdio.h>

typedef struct {
	int student_id;
	int age;
	int year;
} student;

void save_student(student entry);

int main(void)
{
	student entry;
	printf("Please enter your student ID, age, and year: ");
	scanf("%d %d %d", &entry.student_id, &entry.age, &entry.year);
	save_student(entry);	
}

void save_student(student entry)
{
	FILE *fp = fopen("students.txt", "a");
	fprintf(fp, "%d,%d,%d", entry.student_id, entry.age, entry.year);
	fclose(fp);
}