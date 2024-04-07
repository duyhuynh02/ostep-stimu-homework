/*Ex3: 
Next, build a version of the approximate counter. 
Once again, measure its performance as the number of threads varies, as well as the threshold.
Do the numbers match what you see in the chapter?
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define WIDTH 100
#define DEPTH 5

//Implemt Count Min Sketch algorithm 

typedef struct CountMinSketch {
  unsigned int counters[DEPTH][WIDTH];
  unsigned int (*hash_function)(const char *);  
} CountMinSketch;

CountMinSketch* createCountMinSketch(unsigned int (*hash_function)(const char *)) {
    CountMinSketch* cms = (CountMinSketch*)malloc(sizeof(CountMinSketch));
    cms->hash_function = hash_function; 

    for (int i = 0; i < DEPTH; i++) {
        for (int j = 0; i < WIDTH; i++) {
            cms->counters[i][j] = 0; 
        }
    }
    return cms; 
}

void destroyCountMinSketch(CountMinSketch* cms) {
    free(cms);
}

void updateCount(CountMinSketch* cms, const char* element) {
    for (int i = 0; i < DEPTH; i++) {
        unsigned int hash_value = cms->hash_function(element);
        int index = hash_value % WIDTH; 
        cms->counters[i][index]++; 
    }
}

unsigned int estimateCount(CountMinSketch* cms, const char* element) {
    unsigned int min_count = UINT_MAX; 

    for (int i = 0; i < DEPTH; i++) {
        unsigned int hash_value = cms->hash_function(element);
        int index = hash_value % WIDTH; 
        min_count = (cms->counters[i][index] < min_count) ? cms->counters[i][index] : min_count;
    
    }
    return min_count; 
}

unsigned int simpleHash(const char* element) {
    unsigned int hash = 5381; 
    int c; 

    while ((c = *element++) != '\0') {
        hash = ((hash << 5) + hash) + c;
    }
    return hash; 
}

int main() {
    CountMinSketch* cms = createCountMinSketch(simpleHash);

    updateCount(cms, "element1");
    updateCount(cms, "element2");

    //estimate counts 
    unsigned int count1 = estimateCount(cms, "element1");
    unsigned int count2 = estimateCount(cms, "element2");

    printf("Estimated Count for element 1: %u\n", count1);
    printf("Estimated Count for element 2: %u\n", count2); 
    
    //clean up cms 
    destroyCountMinSketch(cms);

    return 0;
}