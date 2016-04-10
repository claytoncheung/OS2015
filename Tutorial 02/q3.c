#include <stdlib.h>
#include <stdio.h>
int main(void)
{
char hello[] = "hello world";
int i=0;
	while(hello[i]!='\0')
	{
	printf("%c", hello[i]);
	i++;
	}
}
