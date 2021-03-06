#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

sem_t sem;
int moving_sum[5] = {0, 0, 0, 0, 0};

struct Num_Info {
	int number;
	int index;
};

void *factorial(void *Num){

	struct Num_Info *my_num = (struct Num_Info*)Num;
	int n = (*my_num).number;
	int i = (*my_num).index;
	int fact = 1;

	for (int j=0; j <=n ; j++){
		fact = fact * j;
	}

	if(moving_sum[i-1] != 0){
	sem_wait(&sem);
	moving_sum[i] = fact + moving_sum[i-1];
	sem_post(&sem);
	}

	else {
	sem_wait(&sem);
	moving_sum[i] = fact;
	sem_post(&sem);
	}

	return NULL;
}

int main(void){

	pthread_t threads[5];
	int num_in;
	struct Num_Info Num[5];

	sem_init(&sem, 0, 1);

	printf("Please enter five numbers: \n");

	for(int i=0; i<5; i++){
		scanf("%d", &num_in);
		Num[i].number = num_in;
		Num[i].index = i;
	}

	for(int i = 0; i<5; i++){
		pthread_create(&threads[i], 0, factorial, (void *) &Num[i]);
	}


	for (int i=0; i<5; i++){
	  	pthread_join(threads[i], NULL);
	 }

	 pthread_exit(NULL);
	 sem_destory(&sem);
	 return 0;
}
