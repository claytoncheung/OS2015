#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	int a[10];
	int i=0;
	FILE *fp = fopen ("question2.txt", "r");

	for(i=0; i<10; i++)
	{
		fscanf (fp, "%d", &a[i]);
		printf("%d\n", a[i]);
	} 
	fclose(fp);

}