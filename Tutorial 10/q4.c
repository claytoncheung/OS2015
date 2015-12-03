#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <mpi.h>

#define MASTER 0
#define DATA_SIZE 1000
#define CHUNK_SIZE 333
#define LOWER	1
#define UPPER	1000

//	Determine if a number is a prime or not by counting the number of
//	roots it has
bool isPrime(int number) {
	int rootCounter = 0;

	for (int i = 2; i < number; i++) {
		if (number%i == 0)
			rootCounter++;
	}

	if (rootCounter == 0)
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
	int i = 0;
	while(results[i] != 0){
		printf("%d, ", i);
		i++;
	}
}
//Given a range of numbers, return the prime numbers within that range
void slave(int proc_id) {
	int chunk[CHUNK_SIZE] = {0};
	int result[CHUNK_SIZE] = {0};
	int n_recv = 0;
	MPI_Status status;
	int arrayCounter = 0;
	int start;

	MPI_Recv(chunk, CHUNK_SIZE, MPI_INT, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
	n_recv = status.MPI_TAG;
	if ((chunk[0]%2) == 0){
		start = chunk[1];
	}
	if ((chunk[0]%2) != 0) {
		start = chunk[0];
	}

	while (n_recv < CHUNK_SIZE) {
		for (int i = start; i < (CHUNK_SIZE+start); i += 2) {
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

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &n_proc);

	MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);

	if (proc_id == MASTER)
		master(n_proc);
	else
		slave(proc_id);

	MPI_Finalize();

}
