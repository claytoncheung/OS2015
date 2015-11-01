/*		Master process prompts user for 5 numbers, writes to numbers.txt
		master process forks and waits for child to terminate
		child reads the 5 numbers from numbers.txt and creates 5 threads
		each thread does n! factorial: calculate factorial, add factorial to total_sum var
		use semaphores for global var, print n!=__________
		child joins on all threads; when all threads are complete, write total_sum to sum.txt and terminate
		parent process reads sum.txt and prints total sum
		*/
		
#include <stdio.h>

int factorial(int number) {
	int f = 1;
	if (number == 0) {
		return f;
	}
	else {
		for (int i = number; i > 0 ; i--) {
			f = f * i;
		}
	}
	return f;
}
void main(){
	int numbers[5];
	
	FILE *fp = fopen ("numbers.txt", "w");
	
	printf("Please enter 5 numbers: ");
	scanf("%d %d %d %d %d", numbers[0], numbers[1], numbers[2], numbers[3], numbers[4]);
}