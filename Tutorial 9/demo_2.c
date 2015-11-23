#include <stdio.h>
#include <omp.h>
int main (int argc, char *argv[])
{
    int thread_num, nthreads = 16;
    
    //This statement is only executed if _OPENMP is defined
    //When it is executed, the max number of threads to be created is = nthreads
    #ifdef _OPENMP
    omp_set_num_threads(nthreads);
    #endif
    printf("Testing OpenMP, you should see each thread print...\n");
    
    //This statement creates nthreads number of threads and begins executing the code within it
    #pragma omp parallel
    {
        //This statement restricts execution of the associated block to a single thread at a time
        #pragma omp critical
        {
         //This statement can only be executed if _OPENMP is defined
         //When it is executed, it prints the number of threads used in execution
          #ifdef _OPENMP
          thread_num = omp_get_thread_num();
          printf("This thread = %d\n", thread_num);
          #endif
        }
    }
    return 0;
}
