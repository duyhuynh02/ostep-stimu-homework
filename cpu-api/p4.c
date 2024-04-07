#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


//the same goes for execle, execlp, execv,... 
int main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        char *myargs[3];
        myargs[0] = strdup("/usr/bin/ls");   // program: "ls" - list files and dirs 
        myargs[1] = strdup(".vscode"); // argument: file to list all files and dirs 
        myargs[2] = NULL;           // marks end of array
        execl(myargs[0], myargs, myargs[2]);  // runs new program ls
        printf("Error"); //this line won't be printed if it fails. 
    } else {
        // parent goes down this path (original process)
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n", rc, wc, (int) getpid());
    }
    return 0;
}