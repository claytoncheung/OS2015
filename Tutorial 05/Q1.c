#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *helloWorld(void *arg)
{
    char *str;
    str=(char*)arg;
	//sleep before printing output
	sleep(2);
	// Show the thread is running
    printf("%s\n",str);

    return NULL;
}

void *goodbye(void *arg)
{
	char *str;
	str = (char*)arg;
	//sleep before printing output
	sleep(2);
	// Show the thread is running
	printf("%s\n", str);

	return NULL;
}

int main() {

    // Thread object
    pthread_t pth;
    pthread_t pth2;

    // Create the thread.
    pthread_create(&pth, 0, helloWorld, (void *) "Hello world!");
    pthread_create(&pth2, 0, goodbye, (void *) "Good bye!");

    // wait for our thread to finish before continuing
    pthread_join(pth, 0);
    pthread_join(pth2, 0);

    return 0;
}
