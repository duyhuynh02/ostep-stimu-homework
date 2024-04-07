#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
   int rc = fork();
   if (rc < 0) {
      // fork failed; exit
      fprintf(stderr, "fork failed\n");
      exit(1);
   } else if (rc == 0) { //child process 
      printf("hello, I am child (pid:%d)\n", (int) getpid());
      //close standard output by STDOUT_FILENO
      close(STDOUT_FILENO);
      //it should be not running
      printf("hello, I am child again (pid:%d)\n", (int) getpid());
   } else {
      // parent goes down this path (original process)
      printf("hello, I am parent of %d (pid:%d)\n", rc, (int) getpid());
   }
   return 0;
}