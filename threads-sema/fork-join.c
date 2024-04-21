#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "common_threads.h"

sem_t s; 
int sval, sval1; 


void *child(void *arg) {
    sleep(1);
    printf("child\n");
    // use semaphore here
    sem_post(&s); //signal here: child is done; 
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    printf("parent: begin\n");
    // init semaphore here
    sem_init(&s, 0, 0);
    Pthread_create(&p, NULL, child, NULL);
    // use semaphore here
    sem_wait(&s); //wait here for child
    printf("parent: end\n");
    return 0;
}

