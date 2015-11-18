#define _XOPEN_SOURCE 600
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

/**
 * A simple forking example. Forks and both child and
 * parent print out different messages.
 */
int main(int argc, char *argv[]) {

    pid_t PID = 0;

    // Create the child.
    PID = fork();

    // Not the child or parent
    if (PID == -1) {
        return 0;
    }

    //Is it a child process or the parent?
    if (PID == 0) {
        //Child process:
        printf("Child Says Hi!\n");

        //Finish on success
        return 0;
    } else {
        //Parent process:
    	FILE *fp = fopen ("child1.txt", "w");
    	fprintf(fp, "child1\n");
    	fclose(fp);
    	FILE *fp1 = fopen ("child2.txt", "w");
    	fprintf(fp1, "child2\n");

        printf("Parent Says Hello\n");
    }

    return 0;
}
