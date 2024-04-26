/* 8-bit unsigned char -> variable can only positive value >= 0, char stands for characters, ragnge from 0 to 255, consumts 8 bits of memory 
one byte checksum

Receive an input file
Print the checksum as output 

Checksum:  take a chunk of data (8-bit or 64-bytes) -> compute a checksum -> produce an input (1 byte)
*/

#include <stdio.h>
#include <stdint.h> 

int main(int argc, char *argv[]) {
    FILE *file; 
    uint8_t checksum; //one byte checksum, no? 
    int character; 

    //check and open the file and see if it's existed 
    if (argc < 2) {
        printf("Missing a file\n");
        return 1;
    }

    file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("Error when opening a file.\n");
        return 1; 
    } 

    //main part, init checksum, read each byte and update the checksum 
    checksum = 0; 
    while ((character = fgetc(file)) != EOF) {
        //read each byte and update the checksum 
        checksum ^= character;
    };

    fclose(file); 

    printf("Checksum: %02x\n", checksum);

    return 0; 

}

