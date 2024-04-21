#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "common_threads.h"

//
// Here, you have to write (almost) ALL the code. Oh no!
// How can you show that a thread does not starve
// when attempting to acquire this mutex you build?
//

typedef struct __ns_mutex_t {
    int room1, room2; //keep track how many threads are in waiting room 
    sem_t mutex; //mutex helps protect the counters 
    sem_t t1, t2; //t1, t2 are turnstiles 
} ns_mutex_t;

ns_mutex_t m; 

void ns_mutex_init(ns_mutex_t *m) {
    m->room1 = 0; 
    m->room2 = 0; 
    sem_init(&m->mutex, 0, 1);
    sem_init(&m->t1, 0, 1);
    sem_init(&m->t2, 0, 0);
}

void ns_mutex_acquire(ns_mutex_t *m) {

}

void ns_mutex_release(ns_mutex_t *m) {
}


typedef struct __tinfo_t {
    int thread_id;
} tinfo_t;


void *worker(void *arg) {
    tinfo_t *t = (tinfo_t *) arg;
    printf("worker %d\n", t->thread_id);
    return NULL;
}

int main(int argc, char *argv[]) {
    assert(argc == 2);
    int num_threads = atoi(argv[1]); 
    assert(num_threads > 0); 

    pthread_t p[num_threads];
    tinfo_t t[num_threads]; 

    printf("parent: begin\n");
    ns_mutex_init(&m);

    int i;
    for (i = 0; i < num_threads; i++) {
        t[i].thread_id = i;
        Pthread_create(&p[i], NULL, worker, &t[i])
    };

    for (i = 0; i < num_threads; i++) 
        Pthread_join(p[i], NULL);

    printf("parent: end\n");
    return 0;
}

