#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> 

int main (int argc, char *argv[]) {
    printf("hello (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { //child (new process)
        int rc_wait = wait(NULL);
        printf("child (pid:%d) (rc_wait:%d)\n ", (int) getpid(), rc_wait);
    } else {
        // int rc_wait = wait(NULL);
        printf("parent of %d (rc_wait:None) (pid:%d)\n", rc, (int) getpid());
    }
    return 0; 
}

