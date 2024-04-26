# Homework (Simulation)
## In this homework, you’ll use checksum.py to investigate various aspects of checksums.
### Questions
1. First just run checksum.py with no arguments. Compute the additive, XOR-based, and Fletcher checksums. Use -c to check your answers.
```sh
$ ./checksum.py

Decimal:          216        194        107         66
Hex:             0xd8       0xc2       0x6b       0x42
Bin:       0b11011000 0b11000010 0b01101011 0b01000010

Add:      583 % 256 = 71 
Xor:      51 (0b00110011)
Fletcher: 216 & 216 => 155 & 116 => 7 & 123 => 73 & 196 => Final answer: 73 | 196 
```
2. Now do the same, but vary the seed (-s) to different values.
```sh
same with question #1 
```
3. Sometimes the additive and XOR-based checksums produce the same checksum (e.g., if the data value is all zeroes). Can you pass in a 4-byte data value (using the -D flag, e.g., -D a,b,c,d) that does not contain only zeroes and leads the additive and XOR-based checksum having the same value? In general, when does this occur? Check that you are correct with the -c flag.
```sh
Look at the binary XOR calculation, if you can find the number e.g., which do not overlap each other, it will be the same thing.

For example:
a: 000000001 | 1
b: 000000010 | 2
c: 000000100 | 4
d: 000001000 | 8 

$ ./checksum.py -D 1,2,4,8 -c

And so on. 
```
4. Now pass in a 4-byte value that you know will produce a different checksum values for additive and XOR. In general, when does this occur?
```sh
$ ./checksum.py -D 1,2,3,4 -c
When the binary options are placed by more than one number 
```

5. Use the simulator to compute checksums twice (once each for a different set of numbers). The two number strings should be different (e.g., -D a1,b1,c1,d1 the first time and -D a2,b2,c2,d2 the
second) but should produce the same additive checksum. In general, when will the additive checksum be the same, even though the data values are different? Check your specific answer with the -c flag.
```sh
./checksum.py -D 4,21,43,123 -c
./checksum.py -D 7,15,43,126 -c
```

6. Now do the same for the XOR checksum.
```sh
We need to calculate the first one first, then reverse the second e..g, 
if the first one is 001 XOR 010 -> 011. Now we need to reverse from 011 and e.g., 100, to find the first number is 111. The same applies for 8 bits number. 
```

7. Now let’s look at a specific set of data values. The first is: -D 1,2,3,4. What will the different checksums (additive, XOR, Fletcher) be for this data? Now compare it to computing these checksums over -D 4,3,2,1. What do you notice about these three checksums? How does Fletcher compare to the other two? How is Fletcher generally “better” than something like the simple additive checksum?
```sh
The sum and XOR is the same, but the Fletcher's algorithm is different. Order matters for Fletcher. 
```

8. No checksum is perfect. Given a particular input of your choosing, can you find other data values that lead to the same Fletcher checksum? When, in general, does this occur? Start with a simple data string (e.g., -D 0,1,2,3) and see if you can replace one of those numbers but end up with the same Fletcher checksum. As always, use -c to check your answers.
```sh
When the second number also have the same value when modulo 255. 
$ ./checksum.py -D 255,1,2,3 -c
```