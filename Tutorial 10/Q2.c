
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>

// Define process 0 as MASTER
#define MASTER 0
#define SLAVE 1

#define DATA_SIZE 10000000

void master(int n_proc)
{
    double data[DATA_SIZE] = { 0 };
    bool running = true;
    int proc = 0;
    MPI_Status status;
    double starttime, endtime;

    for (int i = 0; i < DATA_SIZE; ++i)
    {
        data[i] = i;
    }

    while (running){
        starttime = MPI_Wtime();
        MPI_Send(data, DATA_SIZE, MPI_DOUBLE, SLAVE,n_sent, MPI_COMM_WORLD);

        MPI_Recv(data, DATA_SIZE, MPI_DOUBLE, SLAVE, MPI_ANY_TAG,MPI_COMM_WORLD, &status);
        endtime   = MPI_Wtime();
        printf("Sending->Recieving took %f seconds\n",endtime-starttime);
    }
}


void slave(int proc_id)
{
    double data[DATA_SIZE] = { 0 };  /
    int n_recv = 0;
    bool running = true;
    MPI_Status status;

    MPI_Recv(data, DATA_SIZE, MPI_DOUBLE, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    n_recv = status.MPI_TAG;

    while (running)
    {
        MPI_Send(data, DATA_SIZE, MPI_DOUBLE, MASTER, n_recv, MPI_COMM_WORLD);

        MPI_Recv(data, DATA_SIZE, MPI_DOUBLE, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        n_recv = status.MPI_TAG;
    }
}


int main (int argc, char* argv[])
{
    int proc_id;
    int n_proc;

    // Initialize MPI
    MPI_Init(&argc, &argv);

    // Get the current number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &n_proc);

    // Get the current process id
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);


    if (proc_id == MASTER)
    {
        master(n_proc);
    }
    else
    {
        slave(proc_id);
    }

    // Required to terminate all MPI processes
    MPI_Finalize();
}
