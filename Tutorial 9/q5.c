#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

int main(int argc, char *argv[]) {
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
}
