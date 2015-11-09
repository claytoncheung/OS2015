#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>


#define SHELL "/bin/sh"

int main(int argc, char *argv[]) {

    pid_t PID = 0;

    PID = fork();
    char process[256] = "process.exe";//placeholder for a windows process

    if (PID == 0) {
    	//child
    	execl (SHELL, "clang", "-wall","-Wextra","-std=gnu99","sigtrap.c","-o",process, NULL);

    	sleep(5);
    	kill(PID,SIGINT);
        return 0;

    } else {
    	//parent
        return 0;
    }

    return 0;
}
