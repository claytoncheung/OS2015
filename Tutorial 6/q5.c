/*		Master process prompts user for 5 numbers, writes to numbers.txt
		master process forks and waits for child to terminate
		child reads the 5 numbers from numbers.txt and creates 5 threads
		each thread does n! factorial: calculate factorial, add factorial to total_sum var
		use semaphores for global var, print n!=__________
		child joins on all threads; when all threads are complete, write total_sum to sum.txt and terminate
		parent process reads sum.txt and prints total sum													*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>

int total_sum = 0;
sem_t sem;

void *factorial(void *number) {
	int localNum = (int *) number;
	//Initializes the factorial to 1 in case of 0!
	int f = 1;
	
	//Calculates the factorial if the number>0
	if (localNum != 0) {
		for (int j = localNum; j > 0 ; j--) {
			f *= j;
		}
	}
	sem_wait(&sem);
	// CRITICAL SECTION
	total_sum += f;
	sem_post(&sem);
	// END CRITICAL SECTION
	printf("%d! = %d", localNum, f);
	
	pthread_exit(NULL);
}
int main(){
	int numbers[5];
	pid_t PID = 0;
	//Filenames for easy changing
	const char *numFile = "numbers.txt";
	const char *sumFile = "sum.txt";
	//Open numbers.txt in write mode
	FILE *fp = fopen (numFile, "w");
	
	//Reads in the numbers from user and then prints them to numbers.txt
	printf("Please enter 5 numbers: ");
	scanf("%d %d %d %d %d", numbers[0], numbers[1], numbers[2], numbers[3], numbers[4]);
	fprintf(fp, "%d\n%d\n%d\n%d\n%d", numbers[0], numbers[1], numbers[2], numbers[3], numbers[4]);
	fclose(fp);
	
	//Create child process
	PID = fork();
	//Initialize semaphore
	sem_init (&sem, 0, 1);
	
	if (PID == -1) {
			//Fork failed
		return 0;
	}
	
	else if (PID == 0){
			//Child Process
		int i;
		pthread_t pth[5];
		//Open numbers.txt in read mode
		fp = fopen (numFile, "r");
		
		//create threads
		for (i = 0; i < 5; i++) {
			fscanf(fp, "%d", numbers[i]);
			pthread_create(&pth[i], 0, factorial, (void *) &numbers[i]);
		}
		
		fclose(fp);
		
		//pthread joins
		for (i = 0; i < 5; i++) {
			pthread_join(pth[i], NULL);
		}
		
		//Destroy semaphore
		sem_destroy(&sem);
		//Open sum.txt in write mode
		fp = fopen (sumFile, "w");
		//Print total_sum to file
		fprintf(fp, "The total sum is %d", total_sum);
		fclose(fp);
		exit(0);
	}
	
	else {
			//Parent Process
		//int status;
		int sum;
		//Waits for child process to terminate
		waitpid(PID, NULL, 0);

		//Open sum.txt in read mode
		fp = fopen *sumFile, "r");
		fscanf(fp, "%d", sum);
		printf("The total sum is %d", sum);
		fclose(fp);
		
	}
}