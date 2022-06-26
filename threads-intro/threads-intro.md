# Threads - Introduction 

## Homework (Simulation)
This program, x86.py, allows you to see how different thread interleavings either cause or avoid race conditions. See the README for details on how the program works, then answer the questions below.

### Questions 
1. Let’s examine a simple program, “loop.s”. First, just read and understand it. Then, run it with these arguments (./x86.py -p loop.s -t 1 -i 100 -R dx) This specifies a single thread, an interrupt
every 100 instructions, and tracing of register %dx. What will %dx be during the run? Use the -c flag to check your answers; the answers, on the left, show the value of the register (or memory value) after the instruction on the right has run.
```sh
   dx          Thread 0         
    0   
    -1   1000 sub  $1,%dx
    -1   1001 test $0,%dx
    -1   1002 jgte .top
    -1   1003 halt
```

1. Same code, different flags: (./x86.py -p loop.s -t 2 -i 100 -a dx=3,dx=3 -R dx) This specifies two threads, and initializes each %dx to 3. What values will %dx see? Run with -c to check. 
```sh
 dx          Thread 0                Thread 1         
    3   
    2   1000 sub  $1,%dx     
    2   1001 test $0,%dx     
    2   1002 jgte .top      
    1   1000 sub  $1,%dx    
    1   1001 test $0,%dx   
    1   1002 jgte .top      
    0   1000 sub  $1,%dx    
    0   1001 test $0,%dx    
    0   1002 jgte .top      
    -1   1000 sub  $1,%dx    
    -1  1001 test $0,%dx    
    -1  1002 jgte .top      
    -1  1003 halt           
    3   ----- Halt;Switch -----  ----- Halt;Switch -----  
    2                            1000 sub  $1,%dx       
    2                            1001 test $0,%dx       
    2                            1002 jgte .top         
    1                            1000 sub  $1,%dx       
    1                            1001 test $0,%dx       
    1                            1002 jgte .top         
    0                            1000 sub  $1,%dx       
    0                            1001 test $0,%dx       
    0                            1002 jgte .top         
    -1                            1000 sub  $1,%dx      
    -1                           1001 test $0,%dx       
    -1                            1002 jgte .top         
    -1                            1003 halt              
```
Does the presence of multiple threads affect your calculations? Is there a race in this code?
```
No, it's still in the sequence of the instructions. 
```

3. Run this: ./x86.py -p loop.s -t 2 -i 3 -r -a dx=3,dx=3 -R dx This makes the interrupt interval small/random; use different seeds (-s) to see different interleavings. Does the interrupt frequency change anything?
```sh
./x86.py -p loop.s -s 0 -t 2 -i 3 -r -a dx=3,dx=3 -R dx
./x86.py -p loop.s -s 1 -t 2 -i 3 -r -a dx=3,dx=3 -R dx
./x86.py -p loop.s -s 2 -t 2 -i 3 -r -a dx=3,dx=3 -R dx

Yes.
```

4. Now, a different program, looping-race-nolock.s, which accesses a shared variable located at address 2000; we’ll call this variable value. Run it with a single thread to confirm your understanding: ./x86.py -p looping-race-nolock.s -t 1 -M 2000 What is value (i.e., at memory address 2000) throughout the run? Use -c to check.
