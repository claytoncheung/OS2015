#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <mpi.h>

#define MASTER 0
#define DATA_SIZE 10000
#define CHUNK_SIZE 100
#define LOWER	100
#define UPPER	999
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
	int data[DATA_SIZE] = { 0 };
	int chunk[CHUNK_SIZE] = { 0 };
	int results[DATA_SIZE] = { 0 };
	int total_chunks = DATA_SIZE / CHUNK_SIZE;
	int n_sent = 0, n_recv = 0;
	int proc = 0;
	MPI_Status status;

	for (int i = 0; i < DATA_SIZE; ++i) {
		data[i] = LOWER + i;
	}

	for (int i = 1; i < n_proc; ++i) {
		MPI_Send(&data[n_sent*CHUNK_SIZE], CHUNK_SIZE, MPI_INT, i,
			n_sent, MPI_COMM_WORLD);
		n_sent++;
	}

	for (int i = 0; i < total_chunks; ++i) {
		MPI_Recv(chunk, CHUNK_SIZE, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG,
			MPI_COMM_WORLD, &status);

		proc = status.MPI_SOURCE;
		n_recv = status.MPI_TAG;

		for (int j = 0; j < CHUNK_SIZE; ++j) {
			results[n_recv*CHUNK_SIZE+j] = chunk[j];
		}

		if (n_sent < total_chunks) {
			MPI_Send(&data[n_sent*CHUNK_SIZE], CHUNK_SIZE, MPI_INT, proc,
				n_sent, MPI_COMM_WORLD);
			n_sent++;
		}
	}

	for (int i = 1; i < n_proc; ++i) {
		MPI_Send(chunk, CHUNK_SIZE, MPI_INT, i, CHUNK_SIZE, MPI_COMM_WORLD);
	}

	for (int i = 1; i < DATA_SIZE; ++i) {
		if (data[i] < 1)
			printf("ERROR, DATA ZERO AT %d\n", i);
	}

	for (int i = 0; i < DATA_SIZE; ++i){
		if (results[i] != 0)
			printf("%d ", i);
	}
}
//Given a range of numbers, return the prime numbers within that range
void slave(int n_proc) {
	int chunk[CHUNK_SIZE] = {0};
	int result[CHUNK_SIZE] = {0};
	int n_recv = 0;
	MPI_Status status;
	int arrayCounter = 0;

	MPI_Recv(chunk, CHUNK_SIZE, MPI_INT, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
	n_recv = status.MPI_TAG;

	while (n_recv < CHUNK_SIZE) {
		if (assignedNumbers[0]%2 == 0)
			int start = assignedNumbers[0]+1;
		if (assignedNumbers[0]%2 != 0)
			int start = assignedNumbers[0];

		for (int i = start; i < CHUNK_SIZE; i += 2) {
			if (isPrime(i) == true) {
					result[arrayCounter] = i;
					arrayCounter++;
			}
		}

		MPI_Send(result, CHUNK_SIZE, MPI_INT, MASTER, n_recv, MPI_COMM_WORLD);
		MPI_Recv(chunk, CHUNK_SIZE, MPI_INT, MASTER, MPI_ANY_TAG,
			MPI_COMM_WORLD, &status);
		n_recv = status.MPI_TAG;
	}
}

int main(int argc, char* argv[]) {
	int proc_id;		//Process Rank
	int n_proc;			// Number of Processes
	int slaveNums[2] = {0,0};

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &n_proc);

	MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);


	dividedRange = nearbyint((upperBound - lowerBound)/3);

	int primes[SLAVE_NUM][dividedRange];

	for (int i = 0; i < (SLAVE_NUM + 1); i ++) {
		if (proc_id != MASTER) {
			slaveNums[0] = (lowerBound + (i*dividedRange));
			slaveNums[1] = (upperBound + (i*dividedRange));
			*primes[i] = slave(s);
		}
	}

	if (proc_id == MASTER)
		master(n_proc);
	else
		slave(proc_id);

	MPI_Finalize();

}
