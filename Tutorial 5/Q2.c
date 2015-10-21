
#include <stdio.h>
#include <pthread.h>

void *bellcurve(void *arg)
{
	float *grade;
	grade = (float*)arg;
	*grade *= 1.5;
    printf("%f",*grade);
    return NULL;
}

/**
 * Basic example that showing threading interleaving.
 */
int main(int argc, char *argv[]) {

    // Thread object
    pthread_t pth;
    pthread_t pth2;
    pthread_t pth3;
    pthread_t pth4;
    pthread_t pth5;

    float g1,g2,g3,g4,g5;
    printf("Enter 5 grades separated by spaces");
    scanf("%f %f %f %f %f",g1,g2,g3,g4,g5);

    // Create the thread.
    pthread_create(&pth, 0, bellcurve, (void *) &g1);
    pthread_create(&pth2, 0, bellcurve, (void *) &g2);
    pthread_create(&pth3, 0, bellcurve, (void *) &g3);
    pthread_create(&pth4, 0, bellcurve, (void *) &g4);
    pthread_create(&pth5, 0, bellcurve, (void *) &g5);


    // wait for our thread to finish before continuing
    pthread_join(pth, 0);
    pthread_join(pth2, 0);
    pthread_join(pth3, 0);
    pthread_join(pth4, 0);
    pthread_join(pth5, 0);



    return 0;
}
