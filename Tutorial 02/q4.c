#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	int i;
	for(i=1; i<=10; i++)
	{
		if(i%2==0)
			printf("Even\n");
		else
			printf("Odd\n");
	}
}
