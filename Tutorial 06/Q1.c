#define _XOPEN_SOURCE 600
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {

    pid_t PID = 0;
    pid_t PID1 = 0;

    PID = fork();

    if (PID == 0){
        PID1 = fork();

        if (PID1 == 0){
            sleep(1);
            FILE *fp = fopen ("child1.txt", "r");

            char line[256] = {0};

            fgets(line,256,fp);

            while (!feof(fp)){
                printf(line);
                fgets(line,256,fp);
            }
            fclose(fp);

            return 0;
        }//child 2

        else {
            sleep(1);
            FILE *fp = fopen ("child2.txt", "r");

            char line[256] = {0};
            fgets(line,256,fp);

            while (!feof(fp)){
                printf(line);
                fgets(line,256,fp);
            }
            fclose(fp);
        }//child 1
        return 0;
    }

    else{
        FILE *fp = fopen ("child1.txt", "w");
    	fprintf(fp, "child1\n");
    	fclose(fp);
    	fp = fopen ("child2.txt", "w");
    	fprintf(fp, "child2\n");
    	fclose(fp);

    }//parent

    return 0;
}
