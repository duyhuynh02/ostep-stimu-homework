#include <stdio.h>
#include <stdlib.h>

int main() {
    int number_of_objects = 7; //number of objects e.g., interger
    int *arr; 

    //allocate memory for number of objects 
    arr = (int*) malloc(number_of_objects * sizeof(int)); 

    return 0; 
}

