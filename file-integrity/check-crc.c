/*
Compute the CRC (Cyclic Redundancy Check) 

OKAY LATER!!!!!!!!!!!!!!!!! 
*/

#include <stdio.h>
#include <stdint.h> 
#include <stdlib.h>

uint8_t generatorPolynomial = 0x1A; //0b11010

//CRC


int main(int argc, char *argv[]) {
    FILE *file; 
    long fileSize; 
    char *buffer; 

    //check and open the file and see if it's existed 
    if (argc < 2) {
        printf("Missing a file\n");
        return 1;
    }

    file = fopen(argv[1], "rb"); //read in binary mode 

    if (file == NULL) {
        printf("Error when opening a file.\n");
        return 1; 
    } 
    
    //Determine the file size 
    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    //Allocate memory 
    buffer = (char *)malloc(fileSize);
    if (buffer == NULL) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return 1;
    }

    //now time to read the file
    fread(buffer, 1, fileSize, file);

    //process data for testing first 
    for (long i = 0; i < fileSize; i++) {
        printf("%02x ", buffer[i]);
    }
    
    printf("\n"); 
    fclose(file); 

    return 0; 

}