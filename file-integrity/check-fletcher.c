/*
Computes the Fletcher checksum over an input file.

block D: d1...dn 
s1 = (s1 + di) mod 255
s2 = (s2 + s1) mod 255
*/

#include <stdio.h>
#include <stdint.h> 

int main(int argc, char *argv[]) {
    FILE *file; 
    int character;
    uint8_t checksum, s1, s2;  //checksum 

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

    //main part, init checksum, do the Fletcher's checksum
    checksum = 0; 
    s1 = 0; 
    s2 = 0; 
    while ((character = fgetc(file)) != EOF) {
        //read each byte and update the checksum 
        s1 = (s1 + character) % 255;
        s2 = (s1 + s2) % 255; 
        checksum = s1 + s2; 
    };

    // checksum = s1 + s2; 

    fclose(file); 

    printf("Checksum: %02x\n", checksum);

    return 0; 

}
