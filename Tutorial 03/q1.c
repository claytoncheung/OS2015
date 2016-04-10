#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BUFFER 128


int main(void)
{
	int age;
	float height;
	
	char *name = NULL;
	name = (char *) calloc(BUFFER, sizeof(char));
	
	printf("Enter your name: ");
	scanf("%s", name);
	
	printf("Enter your age: ");
	scanf("%d", &age);
	
	printf("Enter your height in metres: ");
	scanf("%f", &height);
	
	printf("Your name is ");
	for (int i=0; i < strlen(name); ++i){
		printf("%c", name[i]);
	}
	free(name);
	
	printf("\nYour age is %d\n", age);
	printf("Your height is %f metres", height);
	return 0;

}