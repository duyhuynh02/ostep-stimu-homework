#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

int main () {
    FILE *f; 
    int childFileDescriptor, parentFileDescriptor; 

    int rc = fork(); 
    f = fopen("test.txt", "a+"); 

    if (f == NULL) {
        printf("Error opening the file. \n");
        return 1; 
    }; 

   if (rc < 0) {
      fprintf(stderr, "fork failed\n");
      exit(1);
   } else if (rc == 0) {
      // child (new process) 
      childFileDescriptor = fileno(f); 
      printf("Child file descriptor: %d\n", childFileDescriptor);
      fprintf(f, "Child writes something.\n");
   } else {
      // parent goes down this path (original process)
      parentFileDescriptor = fileno(f); 
      printf("Parent file descriptor: %d\n", parentFileDescriptor);
      fprintf(f, "Parent writes something.\n");
   }; 

    fclose(f); 

    return 0; 

};