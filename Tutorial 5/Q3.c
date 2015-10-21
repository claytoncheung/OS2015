
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "Q3.h"

void *bellcurve(void *arg)
{
	student *s;
	s = (float*)arg;
	s->grade *= 1.5;
    printf("%s %s %f",s->name,s->student_id,s->grade);
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

    strcpy(students[0].name,"Bob");strcpy(students[0].student_id,"0001");
    strcpy(students[1].name,"Bob1");strcpy(students[1].student_id,"0002");
    strcpy(students[2].name,"Bob2");strcpy(students[2].student_id,"0003");
    strcpy(students[3].name,"Bob3");strcpy(students[3].student_id,"0004");
    strcpy(students[4].name,"Bob4");strcpy(students[4].student_id,"0005");

    printf("Enter 5 grades separated by spaces");
    scanf("%f %f %f %f %f",students[0].grade,students[1].grade,students[2].grade,students[3].grade,students[4].grade);

    // Create the thread.
    pthread_create(&pth, 0, bellcurve, (void *) &students[0]);
    pthread_create(&pth2, 0, bellcurve, (void *) &students[1]);
    pthread_create(&pth3, 0, bellcurve, (void *) &students[2]);
    pthread_create(&pth4, 0, bellcurve, (void *) &students[3]);
    pthread_create(&pth5, 0, bellcurve, (void *) &students[4]);


    // wait for our thread to finish before continuing
    pthread_join(pth, 0);
    pthread_join(pth2, 0);
    pthread_join(pth3, 0);
    pthread_join(pth4, 0);
    pthread_join(pth5, 0);



    return 0;
}
