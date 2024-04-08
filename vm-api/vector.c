#include <stdio.h>
#include <stdlib.h> 

//vector structure 
typedef struct {
    int *arr; //pointer to the dynamic array; 
    size_t size; //number of elements currently stored; 
    size_t capacity; //capacity of the dynamic array; 
} Vector; 

Vector* create_vector(size_t initial_capacity) {
    Vector *v = (Vector*)malloc(sizeof(Vector));

    if (v == NULL) {
        printf("Allocation failed.\n");
        exit(1);
    }; 

    v->arr = (int*)malloc(initial_capacity * sizeof(int));
    if (v->arr == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }; 

    v->size = 0; 
    v->capacity = initial_capacity;

    return v;  
}

void add_element(Vector* vector, int element) {
    if (vector->size == vector->capacity) {
        vector->capacity *= 2; //double or add more capacity, your choice.
        vector->arr = (int *)realloc(vector->arr, vector->capacity * sizeof(int));
        if (vector->arr == NULL) {
            perror("Memory allocation failed");
            exit(1);
        }; 
    };

    //add element at the end 
    vector->arr[vector->size] = element; 
    vector->size++; 
};

void free_vector(Vector* vector) {
    free(vector->arr);
    free(vector);
}

int main () {
    //create a new vector with an initial capacity 10
    Vector *v = create_vector(10); 

    //adding elements to the vector 
    add_element(v, 10);
    add_element(v, 20);
    add_element(v, 30);

    //now try to run the elements of the vector
    printf("Vector elements are: \n"); 
    for (size_t i = 0; i < v->size; i++) {
        printf("%d: \n", v->arr[i]);
    };

    free_vector(v);

    return 0; 
}