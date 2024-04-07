#include <stdio.h> 
#include <sys/stat.h> 
#include <stdlib.h>

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Missing argument!");
        return 1;
    }; 

    const char* file_path = argv[1];
    struct stat file_stat; 

    if (stat(argv[1], &file_stat) == -1) {
        perror("stat error");
        return 1;
    };

    printf("File size is: %lld bytes\n", (long long)file_stat.st_size);
    printf("Number of blocks: %lld\n", (long long)file_stat.st_blocks);
    printf("Refenrence (or link) count: %lu\n", (unsigned long)file_stat.st_nlink);

    return 0; 
};
