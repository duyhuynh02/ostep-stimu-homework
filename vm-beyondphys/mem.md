# Beyond Physical Memory - Mechanism 

## Measurement (Homework)
This homework introduces you to a new tool, vmstat, and how it can
be used to understand memory, CPU, and I/O usage. Read the associated README and examine the code in mem.c before proceeding to the
exercises and questions below

### Question & Answers 
1. First, open two separate terminal connections to the same machine, so that
you can easily run something in one window and the other.
Now, in one window, run vmstat 1, which shows statistics about machine
usage every second. Read the man page, the associated README, and any
other information you need so that you can understand its output. Leave
this window running vmstat for the rest of the exercises below.
Now, we will run the program mem.c but with very little memory usage.
This can be accomplished by typing ./mem 1 (which uses only 1 MB of
memory). 

How do the CPU usage statistics change when running mem? 
```sh
(us) Time spent running kernel-code (user time, including nice time) increases 
(id) Time spent idle deacrease.
```

Do the numbers in the user time column make sense? 
```sh
No... 
```

How does this change when running more than one instance of mem at once?
```sh
User time is double. 
```

2. Let’s now start looking at some of the memory statistics while running mem.
We’ll focus on two columns: swpd (the amount of virtual memory used) and
free (the amount of idle memory). Run ./mem 1024 (which allocates 1024
MB) and watch how these values change. Then kill the running program
(by typing control-c) and watch again how the values change. 
What do you notice about the values? 
```sh
spwd - the amout of virtual memory used is still the same. 
free - the amount of idle memory is decreased which can be understood. 
```

In particular, how does the free column change when the program exits? 
```sh
When the program exists => the free column will increase. 
```

Does the amount of free memory increase by the expected amount when mem exits?
```sh
Yes.
```

3. We’ll next look at the swap columns (si and so), which indicate how much
swapping is taking place to and from the disk. Of course, to activate these,
you’ll need to run mem with large amounts of memory. First, examine how
much free memory is on your Linux system (for example, by typing cat
/proc/meminfo; type man proc for details on the /proc file system and
the types of information you can find there). One of the first entries in
/proc/meminfo is the total amount of memory in your system. Let’s assume it’s something like 8 GB of memory; if so, start by running mem 4000
(about 4 GB) and watching the swap in/out columns. Do they ever give
non-zero values? 
```sh
Yes. 
```
Then, try with 5000, 6000, etc. What happens to these
values as the program enters the second loop (and beyond), as compared to
the first loop? 
```sh
Increase in first loop, then after that it becomes zero. 
```

How much data (total) are swapped in and out during the
second, third, and subsequent loops? (do the numbers make sense?)
```sh
Zero. 
```

4. Do the same experiments as above, but now watch the other statistics (such
as CPU utilization, and block I/O statistics). How do they change when
mem is running?
```sh
Block I/O: 
 + (bi): increase and decrease not following any pattern. 
 + (bo): Increase in the first loop and then become zero 

```

5. Now let’s examine performance. Pick an input for mem that comfortably
fits in memory (say 4000 if the amount of memory on the system is 8 GB).
How long does loop 0 take (and subsequent loops 1, 2, etc.)? 
```sh
My system is using 3gb memory so 
 ./mem 1500
 allocating 1572864000 bytes (1500.00 MB)
  number of integers in array: 393216000
loop 0 in 964.21 ms (bandwidth: 1555.68 MB/s)
loop 1 in 336.79 ms (bandwidth: 4453.81 MB/s)
loop 2 in 332.77 ms (bandwidth: 4507.66 MB/s)
loop 3 in 323.32 ms (bandwidth: 4639.31 MB/s)
loop 4 in 330.84 ms (bandwidth: 4533.93 MB/s)
loop 5 in 321.84 ms (bandwidth: 4660.71 MB/s)
loop 6 in 317.18 ms (bandwidth: 4729.16 MB/s)
loop 7 in 324.62 ms (bandwidth: 4620.82 MB/s)
loop 8 in 322.82 ms (bandwidth: 4646.52 MB/s)

Around 964.21ms, more than 3x times from loop 1 to the rest. 
```
Now pick a size comfortably beyond the size of memory (say 12000 again assuming 8 GB of memory). How long do the loops take here? How do the bandwidth numbers compare? How different is performance when constantly swapping versus fitting everything comfortably in memory? 
Can you make a graph, with the size of memory used by mem on the x-axis, and the bandwidth of
accessing said memory on the y-axis? Finally, how does the performance of
the first loop compare to that of subsequent loops, for both the case where
everything fits in memory and where it doesn’t?
```sh
./mem 800 
allocating 838860800 bytes (800.00 MB)
  number of integers in array: 209715200
loop 0 in 1390.46 ms (bandwidth: 575.35 MB/s)
loop 1 in 231.01 ms (bandwidth: 3462.99 MB/s)
loop 3 in 168.44 ms (bandwidth: 4749.58 MB/s)

```

```sh 
The bandwidth is smaller than when using smaller memory.
```

6. Swap space isn’t infinite. You can use the tool swapon with the -s flag to
see how much swap space is available. What happens if you try to run mem
with increasingly large values, beyond what seems to be available in swap?
At what point does the memory allocation fail?
```sh
90% of total memory plus total swap. 
```

7. Finally, if you’re advanced, you can configure your system to use different
swap devices using swapon and swapoff. Read the man pages for details.
If you have access to different hardware, see how the performance of swapping changes when swapping to a classic hard drive, a flash-based SSD, and
even a RAID array. How much can swapping performance be improved via
newer devices? How close can you get to in-memory performance?
```sh

```