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
    	kill(PID,SIGTSTP);

    	sleep(10);
    	kill(PID,SIGCONT);

        return 0;

    } else {
    	//parent
    	if (waitpid (PID, 0, 0) != PID){
    	    return 0;
    	}
    }

    return 0;
}
