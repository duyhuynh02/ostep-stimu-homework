#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> 

int main (int argc, char *argv[]) {
    printf("hello (pid:%d)\n", (int) getpid());
    // int rc = fork();

    int child1, child2; 
    child1 = fork(); 
    if (child1 < 0) {
        fprintf(stderr, "fork child 1 failed\n");
        exit(1);
    } else if (child1 == 0) { //child 1 (new process)
        //Put child 1 to sleep 
        sleep(2);
        printf("child 1 (pid:%d) sleep, but the parent should be waiting.\n ", (int) getpid());
    } else {
        child2 = fork(); 
        if (child2 < 0) {
            printf(stderr, "fork child 2 failed\n");
            exit(1);
        } else if (child2 == 0) {
            printf("child 2 (pid:%d) will be killed by the parent.\n ", (int) getpid());
        } else {
            int status, result; 
            result = waitpid(child1, &status, 0); 
            if (result == child1) {
                printf("The parent process finished waiting for the first child (child 1.)\n");
            };
        }
    }
    return 0; 
};



