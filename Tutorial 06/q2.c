#define _BSD_SOURCE
#define _XOPEN_SOURCE 700
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int child(void){

    usleep(1000000);
    printf("Child Process\n");
    return 0;
}

int parent(int PID){

    int got_pid, status;

    while ((got_pid = wait(&status))) {
        if (got_pid == PID){
            printf("Parent Process\n");
            return 0;
        }
    }
    return 0;
}

int main(void) {

    pid_t PID = 0;
    PID = fork();

    if (PID == -1) {
        return 0;
    }
    if (PID == 0) {
        child();
    } 
    else {
        parent(PID);
    }

    return 0;
}
