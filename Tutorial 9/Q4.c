#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

int main(void)
{
	int n, sum;
	n = 100;
	int a[n][n], b[n][n], multiplied[n][n];

	for(int i=0;i<n;i++){
		for(int j=0;i<n;i++){
			a[i][j] = j;
			b[i][j] = j;
		}
	}

	for(int i=0;i<n;i++){
		for(int j=0;i<n;i++){
			printf("%d		%d\n", a[i][j], b[i][j]);
		}
	}


	#ifdef _OPENMP
	omp_set_num_threads(n);
	#endif

	#pragma omp parallel for private(multiplied, sum)
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++)
			{
				multiplied[i][j] = sum;
				
				for(int k=0;k<n;k++)
				{
					sum = sum + a[j][k]*b[k][j];
				}
			}

		}

}
