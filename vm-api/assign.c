#include <stdio.h>
#include <stdlib.h>

int main() {
    int number_of_slots = 100; //number of objects e.g., interger
    int *arr; 

    //allocate memory for number of objects 
    arr = (int*) malloc(number_of_slots * sizeof(int)); 
    arr[99] = 0; 
    // arr[100] = 0; 

    printf("arr[99] = %d\n", arr[99]);
    // printf("arr[100] = %d\n", arr[100]);
    free(arr[50]);

    return 0; 
}

