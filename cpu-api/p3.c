#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h> 

int main(int argc, char *argv[])
{
   int p[2]; 
   int rc = fork();

   if (pipe(p) < 0) 
     exit(1); 

   if (rc < 0) {
      // fork failed; exit
      fprintf(stderr, "fork failed\n");
      exit(1);
   } else if (rc == 0) {
      // child (new process)
    //   write(p[1], "Hello", 16); 
      printf("hello"); 
      close(p[0]); 
      write(p[1], "hello", 6);
      close(p[1]); 
   } else {
      // parent goes down this path (original process)
      write(p[1], "Hello", 16); 
      printf("goodbye\n"); 
      close(p[1]); 

      char buffer[4]; 
      read(p[0], buffer, 4); 
      printf("Goodbye");
      close(p[0]);
   }; 

   return 0;
}