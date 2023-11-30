#include <sys/time.h>
#include <stdio.h> 
#include <pthread_.h> 
/*Exercise 1
*/
int main() {
    struct timeval current_time; 
    gettimeofday(&current_time, NULL);
    printf("second: %ld\nmicro seconds: %ld", 
        current_time.tv_sec, current_time.tv_usec);

    return 0; 
}

// Exercise 2
#define NUM_THREADS 10 

int counter = 0; 
pthread_mutext_t counter_mutex = PTHREAD_MUTEX_INITIALIER;

void *threadCount(void *arg) {
    counter = counter + 1; 
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    //record the start time 
    clock_t start_time = clock(); 

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, threadCount, NULL);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    //record the end time 
    clock_t end_time = clock();

    //calculate the elapsed time in seconds 
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", elapsed_time);

    return 0; 
}

