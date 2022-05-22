# VM Segmentation

## Homework (Stimulation)
This program allows you to see how address translations are performed in a system with segmentation. See the README for details.

### Questions 
1. First let’s use a tiny address space to translate some addresses. Here’s a simple set of parameters with a few different random seeds; can you translate the addresses?
segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 0

```sh
  Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
  Segment 0 limit                  : 20
=> BASE-BOUND: 0 -> 20 

  Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
  Segment 1 limit                  : 20
=> BASE-BOUND: 512 -> 492 

Virtual Address Trace
  VA  0: 0x0000006c (decimal:  108) --> Segment 1 (decimal 492) => VALID // 512 - (128 - 108) = 492 
  VA  1: 0x00000061 (decimal:   97) --> Segment 1 (decimal 481) => INVALID  
  VA  2: 0x00000035 (decimal:   53) --> Segment 0 (decimal 53) => INVALID 
  VA  3: 0x00000021 (decimal:   33) --> Segment 0 (decimal 33) => INVALID 
  VA  4: 0x00000041 (decimal:   65) --> Segment 1 (decimal 449) => INVALID  
```

segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 1
```sh
  Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
  Segment 0 limit                  : 20
=> 0 -> 19

  Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
  Segment 1 limit                  : 20
=> 511 -> 492 

Virtual Address Trace
  VA  0: 0x00000011 (decimal:   17) --> Segment 0 (decimal 17) => VALID 
  VA  1: 0x0000006c (decimal:  108) --> Segment 1 (decimal 492) => VALID 
  VA  2: 0x00000061 (decimal:   97) --> Segment 1 (decimal 481) => INVALID 
  VA  3: 0x00000020 (decimal:   32) --> Segment 0 (decimal 32) => INVALID 
  VA  4: 0x0000003f (decimal:   63) --> Segment 0 (decimal 63) => INVALID 
```


segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 2
```sh
Segment register information:

  Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
  Segment 0 limit                  : 20
=> 0 -> 19 

  Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
  Segment 1 limit                  : 20
=> 511 -> 492 

Virtual Address Trace
  VA  0: 0x0000007a (decimal:  122) --> Segment 1 (decimal 506) => VALID 
  VA  1: 0x00000079 (decimal:  121) --> Segment 1 (decimal 505) => VALID 
  VA  2: 0x00000007 (decimal:    7) --> Segment 0 (decimal 7) => VALID 
  VA  3: 0x0000000a (decimal:   10) --> Segment 0 (decimal 10) => VALID 
  VA  4: 0x0000006a (decimal:  106) --> Segment 1 (decimal 490) => INVALID 

```

2. Now, let’s see if we understand this tiny address space we’ve constructed (using the parameters from the question above). What is
the highest legal virtual address in segment 0? What about the lowest legal virtual address in segment 1? What are the lowest and
highest illegal addresses in this entire address space? Finally, how
would you run segmentation.py with the -A flag to test if you
are right?
```sh
For segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 2: 

- Highest legal virtual address in segment 0: 19
- Lowest legal virtual address in segment 1: 108 
- Lowest illegal address in this entire address space: 20 
- Highest illegal address: 492

segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 2 -A 19,108,20,107 -c 
```

3. Let’s say we have a tiny 16-byte address space in a 128-byte physical
memory. What base and bounds would you set up so as to get
the simulator to generate the following translation results for the
specified address stream: valid, valid, violation, ..., violation, valid,
valid? Assume the following parameters:
segmentation.py -a 16 -p 128
-A 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
--b0 ? --l0 ? --b1 ? --l1 ?
```sh
```

4. Assume we want to generate a problem where roughly 90% of the
randomly-generated virtual addresses are valid (not segmentation
violations). How should you configure the simulator to do so?
Which parameters are important to getting this outcome?
```sh
```

5. Can you run the simulator such that no virtual addresses are valid? How? 
```sh
```

```sh
  -h, --help            show this help message and exit
  -s SEED, --seed=SEED  the random seed
  -A ADDRESSES, --addresses=ADDRESSES
                        a set of comma-separated pages to access; -1 means
                        randomly generate
  -a ASIZE, --asize=ASIZE
                        address space size (e.g., 16, 64k, 32m, 1g)
  -p PSIZE, --physmem=PSIZE
                        physical memory size (e.g., 16, 64k, 32m, 1g)
  -n NUM, --numaddrs=NUM
                        number of virtual addresses to generate
  -b BASE0, --b0=BASE0  value of segment 0 base register
  -l LEN0, --l0=LEN0    value of segment 0 limit register
  -B BASE1, --b1=BASE1  value of segment 1 base register
  -L LEN1, --l1=LEN1    value of segment 1 limit register
  -c                    compute answers for me
```
