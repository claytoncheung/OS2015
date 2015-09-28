#include <stdlib.h>
#include <stdio.h>
int main(void)
{
double num[5]={1.2, 5.5, 2.1, 3.3, 3.3};
int i;
for(i=1;i<5;i++) //Start at i=1 because there is no value before 1.2
	{
	if(num[i]==num[i-1])
		puts("the same");
	else if(num[i]>num[i-1])
		puts("greater than");
	else if(num[i]<num[i-1])
		puts("less than");
}
}
