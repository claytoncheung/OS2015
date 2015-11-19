/*
    This code was executed 3 times per thread count in order to accurately
    determine the time required to complete the calculations.
    My laptop with an Intel Core i5-5300U CPU averaged around
    20.5s on 1 thread, 14.5s on 2 threads, 14.0-14.8s for the rest.
    It is clear that using two threads is optimal.    
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    double start = omp_get_wtime();
    static int n = 100000000;
    int nthreads;
    float dx, x, y;
    dx = 1/(n+1);
    FILE *fp = fopen("calculations.txt", "w");

    if (argc > 1)
        nthreads = atoi(argv[1]);

    #ifdef _OPENMP
    omp_set_num_threads(nthreads);
    #endif

    #pragma omp parallel for private(x)
    for (int i = 0; i < n; i++){
        x = i * dx;
        y = exp(x) * cos(x) * sin(x) * sqrt((5*x)+6);

        #pragma omp critical
        if ((i%1000000) == 0){
            fprintf(fp, "%d, %f, %f\n", i, x, y);
        }
    }

    fclose(fp);
    double end = omp_get_wtime();
    printf("Time elapsed: %f", end - start);
}
