/* Next, create a little program that uses a certain amount of memory, called memory-user.c. 
This program should take one commandline argument: the number of megabytes of memory it will use. 
When run, it should allocate an array, and constantly stream through the array, 
touching each entry. The program should do this indefinitely, or, perhaps, for a certain amount of time also specified at the command line.
*/

#include <stdio.h>
#include <stdlib.h>

int main(int mem) {
    int* arr; 

    arr = (int*) malloc(sizeof(mem) * 1024 * 1024); //from MB to bytes 
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        exit(1); 
    }; 

    //Access the allocated array and it will run indefinitely until terminateed 
    while (1) {
        for (int i = 0; i < (mem * 1024 * 1024); ++i) {
            printf("%d ", arr[i]);
        }; 
    }

    //Free after done 
    free(arr);
    return 0; 
}