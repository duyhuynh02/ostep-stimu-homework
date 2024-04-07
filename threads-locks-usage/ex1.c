#include <sys/time.h>
#include <stdio.h> 
#include <pthread.h> 
/*
1. We’ll start by redoing the measurements within this chapter. 
Use the call gettimeofday() to measure time within your program.
How accurate is this timer? What is the smallest interval it can measure? 
Gain confidence in its workings, as we will need it in all subsequent questions. 
You can also look into other timers, such as the cycle counter available on x86 via the rdtsc instruction.
*/

int main() {
    struct timeval current_time; 
    gettimeofday(&current_time, NULL);
    printf("seconds: %ld\nmicro seconds: %ld", 
        current_time.tv_sec, current_time.tv_usec);

    return 0; 
}