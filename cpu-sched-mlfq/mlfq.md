# Scheduling: The multi-level feedback queue 

## Homework (Simulation)

Run the program 'mlfq.py', see the README for details.

### Questions 

1. Run a few randomly-generated problems with just two jobs and
two queues; compute the MLFQ execution trace for each. Make
your life easier by limiting the length of each job and turning off
I/Os.

``` 
ANSWER: $ python3 mlfq.py -j 2 -n 2 -m 10 -M 0  
```

2. How would you run the scheduler to reproduce each of the examples in the chapter?
``` 
ANSWER: 
//Figure 8.2
$ python3 mlfq.py -n 3 -q 10 -l 0,200,0 -c 

//Figure 8.3: 
$ python3 mlfq.py -n 3 -q 10 -l 0,180,0:100,20,0 -c

//Figure 8.4: 
$ python3 mlfq.py -q 10 -l 0,186,0:0,14,1 -S -i 9 -c

//Figure 8.5: $ python3 mlfq.py -l0,120,0:100,50,0:100,50,0 -q 10 -i 5 -S 

//Figure 8.6: 
$ python3 mlfq.py -n 3 -q 10 -i 1 -l 0,180,0:80,100,9 -S -c (no gaming tolerance)

$ python3 mlfq.py -n 3 -q 10 -i 1 -l 0,180,0:80,100,9 -c (with gaming tolerance)

//Figure 8.7: $ python3 mlfq.py -Q 10,20,40 -a 2 -l 0,140,0:0,140,0 -c
``` 

3. How would you configure the scheduler parameters to behave just
like a round-robin scheduler?
``` 
ANSWER: will comeback soon. 
``` 

4. Craft a workload with two jobs and scheduler parameters so that
one job takes advantage of the older Rules 4a and 4b (turned on
with the -S flag) to game the scheduler and obtain 99% of the CPU
over a particular time interval.
``` 
ANSWER: will comeback soon. 
``` 

5. Given a system with a quantum length of 10 ms in its highest queue,
how often would you have to boost jobs back to the highest priority
level (with the -B flag) in order to guarantee that a single longrunning (and potentially-starving) job gets at least 5% of the CPU?
```
ANSWER: 200 ms.
$ python3 mlfq.py -n 3 -q 10 -l 0,200,0:0,200,1:0,200,1 -i 1 -S -B 200 -c
```

6. One question that arises in scheduling is which end of a queue to
add a job that just finished I/O; the -I flag changes this behavior
for this scheduling simulator. Play around with some workloads
and see if you can see the effect of this flag.
``` 
ANSWER: will comeback soon. 
```   