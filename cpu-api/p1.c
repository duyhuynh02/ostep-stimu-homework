#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
   int x = 10;
   int rc = fork();
   if (rc < 0) {
      // fork failed; exit
      fprintf(stderr, "fork failed\n");
      exit(1);
   } else if (rc == 0) {
      // child (new process)
      printf("hello, I am child (pid:%d)\n", (int) getpid());
      printf("the x variable in child process: (x:%d)\n", x); 
      x = 11; 
      printf("the x (2nd time) variable in child process: (x:%d)\n", (int) x); 
   } else {
      // parent goes down this path (original process)
      printf("hello, I am parent of %d (pid:%d)\n", rc, (int) getpid());
      x = 12; 
      printf("the x (2nd time) variable in parent process: (x:%d)\n", (int) x); 
   }
   printf("the final x will be: (x:%d)\n", x); 
   return 0;
}