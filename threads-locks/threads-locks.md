# HOMEWORK (Simulation)
This program, x86.py, allows you to see how different thread interleavings either cause or avoid race conditions. See the README for details on how the program works and answer the questions below.

## Questions 
1. Examine flag.s. This code “implements” locking with a single memory flag. Can you understand the assembly?
```sh
Yes 
```

2. When you run with the defaults, does flag.s work? Use the -M and -R flags to trace variables and registers (and turn on -c to see their values).
Can you predict what value will end up in flag?
```sh
Yes. 
./x86.py -p flag.s -M flag,count -R ax,bx
flag = 0
```

3. Change the value of the register %bx with the -a flag (e.g., -a bx=2,bx=2
if you are running just two threads). What does the code do? How does it
change your answer for the question above?
```sh
Still the same (but in this command each thread run twice!)=> flag = 0; 
```

4. Set bx to a high value for each thread, and then use the -i flag to generate
different interrupt frequencies; what values lead to a bad outcomes? Which
lead to good outcomes?
```sh
Bad outcomes: <= 3 (+11)
Good outcomes: > 3 (+11)
```

5. Now let’s look at the program test-and-set.s. First, try to understand the code, which uses the xchg instruction to build a simple locking primitive. How is the lock acquire written? How about lock release?
```sh
xchg %ax, mutex     # atomic swap of 1 and mutex

Lock release -> 
mov  $0, mutex
```

6. Now run the code, changing the value of the interrupt interval (-i) again, and making sure to loop for a number of times. Does the code always work as expected? Does it sometimes lead to an inefficient use of the CPU? How could you quantify that?
```sh
Yes.
NO.
```

7. Use the -P flag to generate specific tests of the locking code. For example, run a schedule that grabs the lock in the first thread, but then tries to acquire it in the second. Does the right thing happen? What else should you test?
```sh
./x86.py -p test-and-set.s -M count,mutex -R ax,bx -i 1 -P 0011 -c
Yes - fairness between 2 threads. 
```

8. Now let’s look at the code in peterson.s, which implements Peterson’s algorithm (mentioned in a sidebar in the text). Study the code and see if you can make sense of it.
```sh
Yes
```

9. Now run the code with different values of -i. What kinds of different behavior do you see? Make sure to set the thread IDs appropriately (using -a bx=0,bx=1 for example) as the code assumes it.
```sh
./x86.py -p peterson.s -M flag,count,turn -R ax,bx,cx,fx -i 25 -a bx=0,bx=1 -c
```

10. Can you control the scheduling (with the -P flag) to “prove” that the code works? What are the different cases you should show hold? Think about mutual exclusion and deadlock avoidance.
```sh
$ ./x86.py -p peterson.s -M count,flag,turn -R ax,bx,cx,fx -a bx=0,bx=1 -c -P 0000011111
```

11. Now study the code for the ticket lock in ticket.s. Does it match the code in the chapter? Then run with the following flags: -a bx=1000,bx=1000 (causing each thread to loop through the critical section 1000 times). Watch what happens; do the threads spend much time spin-waiting for the lock?
```sh

```
