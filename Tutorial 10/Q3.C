#include <stdio.h>
#include <mpi.h>

#define send_data_tag 2001
#define return_data_tag 2002
#define array_size 100

int main(int argc, char **argv)
{
	int a[array_size][array_size], b[array_size][array_size], c[array_size][array_size], received_a[array_size][array_size], received_b[array_size][array_size];
	int sum, my_id, master_process, num_procs,an_id, avg_rows_per_process, avg_cols_per_process, 
		num_rows_received, num_cols_received, start_row, end_row, start_col, end_col, total_data_sent;
	MPI_Status status;

	// Initialize array variables


	for(int i=0;i<array_size;i++){
		for(int j=0;j<array_size;j++){
			a[i][j] = i;
			b[i][j] = j;
		}
	}


	printf("------These are initial arrays------\n");
	printf("===ARRAY a===\n");
	for(int i=0;i<array_size;i++){
		for(int j=0;j<array_size;j++){
			printf("%d ", a[i][j]);
			if (j == (array_size - 1))
				printf("\n");
		}
	}

	printf("===ARRAY b===\n");
	for(int i=0;i<array_size;i++){
		for(int j=0;j<array_size;j++){
			printf("%d ", b[i][j]);
			if (j == (array_size - 1))
				printf("\n");
		}
	}


	// From this point on, every process executes a seperate copy of program

	MPI_Init(&argc, &argv);
	
	master_process = 0;

	MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

	if(my_id == master_process)
	{

		avg_rows_per_process = array_size / num_procs;
		avg_cols_per_process = array_size / num_procs;

		for(an_id = 1; an_id < num_procs; an_id++)
		{
			start_row = an_id * avg_rows_per_process + 1;
			end_row   = (an_id + 1) * avg_rows_per_process;

			start_col = an_id * avg_cols_per_process + 1;
			end_col   = (an_id + 1) * avg_cols_per_process;

			if((array_size - end_row) < avg_rows_per_process)
				end_row = array_size - 1;

			if ((array_size - end_col) < avg_cols_per_process)
				end_col = array_size - 1;

			total_data_sent = (end_row - start_row + 1) + (end_col - start_col + 1);

			MPI_Send( &avg_rows_per_process, 1, MPI_INT, an_id, send_data_tag, MPI_COMM_WORLD);
			MPI_Send( &avg_cols_per_process, 1, MPI_INT, an_id, send_data_tag, MPI_COMM_WORLD);
			MPI_Send( &total_data_sent, 1, MPI_INT, an_id, send_data_tag, MPI_COMM_WORLD);
			MPI_Send( &start_row, 1, MPI_INT, an_id, send_data_tag, MPI_COMM_WORLD);
			MPI_Send( &start_col, 1, MPI_INT, an_id, send_data_tag, MPI_COMM_WORLD);

			MPI_Send( &a[start_row][start_col], total_data_sent, MPI_INT, an_id, send_data_tag, MPI_COMM_WORLD);
			MPI_Send( &b[start_row][start_col], total_data_sent, MPI_INT, an_id, send_data_tag, MPI_COMM_WORLD);
		}

		for(int i=0;i<avg_rows_per_process;i++){
			for(int j=0;j<avg_cols_per_process;j++)
			{
				c[i][j] = sum;
				printf("%d\n", c[i][j]);
				for(int k=0;k<avg_rows_per_process;k++)
				{
					sum = sum + a[j][k]*b[k][j];
				}
			}
		}

		for(an_id = 1; an_id < num_procs; an_id++)
		{

			MPI_Recv( &c[start_col][start_col], total_data_sent, MPI_LONG, MPI_ANY_SOURCE, send_data_tag, MPI_COMM_WORLD, &status);

		}
	}

		else 
		{

			MPI_Recv( &num_rows_received, 1, MPI_INT, master_process, send_data_tag, MPI_COMM_WORLD, &status);
			MPI_Recv( &num_cols_received, 1, MPI_INT, master_process, send_data_tag, MPI_COMM_WORLD, &status);
			MPI_Recv( &total_data_sent, 1, MPI_INT, master_process, send_data_tag, MPI_COMM_WORLD, &status);
			MPI_Recv( &start_row, 1, MPI_INT, master_process, send_data_tag, MPI_COMM_WORLD, &status);
			MPI_Recv( &start_col, 1, MPI_INT, master_process, send_data_tag, MPI_COMM_WORLD, &status);

			MPI_Recv( &received_a, total_data_sent, MPI_INT, master_process, send_data_tag, MPI_COMM_WORLD, &status);
			MPI_Recv( &received_b, total_data_sent, MPI_INT, master_process, send_data_tag, MPI_COMM_WORLD, &status);

			for(int i=0;i<avg_rows_per_process;i++){
			for(int j=0;j<avg_cols_per_process;j++)
			{
				c[i][j] = sum;
				for(int k=0;k<avg_rows_per_process;k++)
				{
					sum = sum + received_a[j][k] * received_b[k][j];
				}
			}

			MPI_Send( &c[start_row][start_col], total_data_sent, MPI_LONG, master_process, return_data_tag, MPI_COMM_WORLD);
			}

	

		}

	MPI_Finalize();

	printf("------The Multiplied Array------\n");
	for(int i=0; i<array_size; i++){
		for (int j = 0; j < array_size; j++)
		{
			printf("%d ", c[i][j]);
			if(j == (array_size - 1))
				printf("\n");
		}
	}

}
