#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <Q4.h>

int buffer[5] = { 0 };
sem_t sem;

void *producer(void *arg){
	int count = 0;
	int *numbers[NUMBERS];
    *numbers =(int*)arg;
	while (count < 10){
		for (int n = 0; n < 5; n++){
			if (buffer[n] == 0){
				sem_wait(&sem);
				buffer[n] = *numbers[count];
				printf("Produced %i",*numbers[count]);
				count++;
				sem_post(&sem);
			}
		}

		usleep(rand() % 100 + 1);
	}
	return NULL;
}

void *consumer(void *arg){
	int count = 0;
	while (count < 10){
		for (int n = 0; n < 5; n++){
			if (buffer[n] != 0){
				sem_wait(&sem);
				printf("Consumed %i",buffer[count]);
				buffer[count] = 0;
				count++;
				sem_post(&sem);
			}
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
    numbers[0],numbers[1],numbers[2],numbers[3],numbers[4],
	numbers[5],numbers[6],numbers[7],numbers[8],numbers[9]);

	pthread_create(&pth, 0, producer, (void *) &numbers);
	pthread_create(&pth2, 0, consumer, (void *) NULL);

	pthread_join(pth, 0);
	pthread_join(pth2, 0);

	sem_destroy(&sem);

	return 0;
}
