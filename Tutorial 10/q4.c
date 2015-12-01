#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <mpi.h>

#define MASTER 0
#define SLAVE_NUM 3

//	Determine if a number is a prime or not by counting the number of
//	roots it has
bool isPrime(int number) {
	int rootCounter = 0;

	for (int i = 0; i <= number; i++) {
		if (number%i == 0)
			rootCounter++;
	}

	if (rootCounter < 3)
		return true;
	else
		return false;
}

void master(int n_proc) {

}
//Given a range of numbers, return the prime numbers within that range
void slave(int n_proc) {
	int *localPrimes;
	localPrimes = malloc((assignedNumbers[1] - assignedNumbers[0]) * sizeof(int));
	localPrimes = NULL;
	int arrayCounter = 0;
	int start;
	MPI_Status status;

	if (assignedNumbers[0]%2 == 0)
		start = assignedNumbers[0]+1;
	if (assignedNumbers[0]%2 != 0)
		start = assignedNumbers[0];

	for (int i = start; i < assignedNumbers[1]; i += 2) {
		if (isPrime(i) == true) {
				localPrimes[arrayCounter] = i;
				arrayCounter++;
		}
	}

	return localPrimes;
}

int main(int argc, char* argv[]) {
	int proc_id;		//Process Rank
	int n_proc;			// Number of Processes
	int slaveNums[2] = {0,0};
	int lowerBound, upperBound, dividedRange;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &n_proc);

	MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);

	if (argc > 1) {
		sscanf(argv[1], "%d", &lowerBound);
		sscanf(argv[2], "%d", &upperBound);
	}

	dividedRange = nearbyint((upperBound - lowerBound)/3);

	int primes[SLAVE_NUM][dividedRange];

	for (int i = 0; i < (SLAVE_NUM + 1); i ++) {
		if (proc_id != MASTER) {
			slaveNums[0] = (lowerBound + (i*dividedRange));
			slaveNums[1] = (upperBound + (i*dividedRange));
			*primes[i] = slave(s);
		}
	}

	MPI_Finalize();

	for (int i = 0; i < SLAVE_NUM; i++) {
		int j = 0;
		while (primes[i][j] != NULL){
			printf("%d ", primes[i][j]);
		}
		j++;
		printf("\n");
	}
}
