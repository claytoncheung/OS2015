#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "Q4.h"

int buffer[5] = { 0 };
sem_t sem;

void *producer(void *arg){
	int count = 0;
	int *numbers = (int*)arg;
	while (count < 10){
		for (int n = 0; n < 5; n++){
            sem_wait(&sem);
			if (buffer[n] == 0){
				buffer[n] = numbers[count];
				printf("Produced %i\n",buffer[n]);
				count++;
			}
			sem_post(&sem);
		}

		usleep(rand() % 100 + 1);
	}
    return NULL;
}

void *consumer(void *arg){
	int count = 0;
	while (count < 10){
		for (int n = 0; n < 5; n++){
			sem_wait(&sem);
			if (buffer[n] != 0){
				printf("Consumed %i\n",buffer[n]);
				buffer[n] = 0;
				count++;
			}
            sem_post(&sem);
		}
		usleep(rand() % 100 + 1);
	}
    return NULL;
}

int main(void){

	int numbers[NUMBERS];

	pthread_t pth;
	pthread_t pth2;

	sem_init(&sem, 0, 1);

	printf("Enter 10 numbers separated by spaces: ");
	scanf("%i %i %i %i %i %i %i %i %i %i",
    &numbers[0],&numbers[1],&numbers[2],&numbers[3],&numbers[4],
	&numbers[5],&numbers[6],&numbers[7],&numbers[8],&numbers[9]);

	pthread_create(&pth, 0, producer, (void *) &numbers);
	pthread_create(&pth2, 0, consumer, (void *) NULL);
    
	pthread_join(pth, NULL);
	pthread_join(pth2, NULL);
    
    for (int i=0;i<5;i++){
        printf("%d ", buffer[i]);
    }
    printf("\n");

	sem_destroy(&sem);

	return 0;
}
