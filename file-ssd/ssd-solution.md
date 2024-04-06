# Homework (Simulation)

## This section introduces ssd.py, a simple SSD simulator you can use to understand better how SSDs work. Read the README for details on how to run the simulator. It is a long README, so boil a cup of tea (caffeinated likely necessary), put on your reading glasses, let the cat curl upon your lap1, and get to work.

### Questions
1. The homework will mostly focus on the log-structured SSD, which is simulated with the “-T log” flag. We’ll use the other types of
SSDs for comparison. First, run with flags -T log -s 1 -n 10 -q. Can you figure out which operations took place? Use -c to check your answers (or just use -C instead of -q -c). Use different values of -s to generate different random workloads.
```sh
cmd   0:: command(??) -> write(12, u) | success
cmd   1:: command(??) -> write(32, M) | success 
cmd   2:: read(32) -> M 
cmd   3:: command(??) -> write(38, 0) | success
cmd   4:: command(??) -> write(36, e) | success 
cmd   5:: command(??) ->  trim(36, e) | success 
cmd   6:: read(32) -> M
cmd   7:: command(??) -> trim(32, M) | success 
cmd   8:: read(12) -> u
cmd   9:: read(12) -> u

The ame for different seeds 
```
2. Now just show the commands and see if you can figure out the intermediate states of the Flash. Run with flags -T log -s 2 -n
10 -C to show each command. Now, determine the state of the Flash between each command; use -F to show the states and see if you were right. Use different random seeds to test your burgeoning expertise.
```sh
Same with pset #1 
```
3. Let’s make this problem ever so slightly more interesting by adding the -r 20 flag. What differences does this cause in the commands? Use -c again to check your answers.
```sh
I don't know, more read? And after a failed read, it tried to write first? 
```
4. Performance is determined by the number of erases, programs, and reads (we assume here that trims are free). Run the same workload again as above, but without showing any intermediate states (e.g., -T log -s 1 -n 10). Can you estimate how long this workload will take to complete? (default erase time is 1000 microseconds, program time is 40, and read time is 10) Use the -S flag to check your answer. You can also change the erase, program, and read times with the -E, -W, -R flags.
```sh
Erase time is 1000 microseconds, program time is 40 second, and read time is 10 microsecond: 

First block (0) first need to erase all the pages (set the state to Erased (E)), so it take 1000 ms. 
Write 4 characters -> 40 x 4 = 160 ms 
Trim 2 characters -> 0 ms 
I assume it read 4 times too ->  10 x 4 = 40 ms 
=> So total: 1200 ms
```
5. Now, compare performance of the log-structured approach and the (very bad) direct approach (-T direct instead of -T log). First, estimate how you think the direct approach will perform, then check your answer with the -S flag. In general, how much better will the log-structured approach perform than the direct one?
```sh
Give the same parameters as question 4, and the worst case:
It could be anywhere on different block, so it could be on 4 blocks ->
Errase time: 4000 ms 
Write: more than 160 ms
Read: more than 40 ms 
So around more than > 4000ms 

Actual time: 4350 ms 
Comparing: Log struct has a result better than 4 times. 
```

6. Let us next explore the behavior of the garbage collector. To do so, we have to set the high (-G) and low (-g) watermarks appropriately. First, let’s observe what happens when you run a larger workload to the log-structured SSD but without any garbage collection. To do this, run with flags -T log -n 1000 (the high watermark default is 10, so the GC won’t run in this configuration). What do you think will happen? Use -C and perhaps -F to see.
```sh
A lot of failure due to run out of storage. 
```

7. To turn on the garbage collector, use lower values. The high watermark (-G N) tells the system to start collecting once N blocks have been used; the low watermark (-g M) tells the system to stop collecting once there are only M blocks in use. What watermark values do you think will make for a working system? Use -C and -F to show the commands and intermediate device states and see.
```sh
Use any -G with N <= 7 
With -g, there is no value, since we do not want to stop collection, don't we? 
```
8. One other useful flag is -J, which shows what the collector is doing when it runs. Run with flags -T log -n 1000 -C -J to see both the commands and the GC behavior. What do you notice about the GC? The final effect of GC, of course, is performance. Use -S to look at final statistics; how many extra reads and writes occur due to garbage collection? Compare this to the ideal SSD (-T ideal); how much extra reading, writing, and erasing is there due to the nature of Flash? Compare it also to the direct approach; in what way (erases, reads, programs) is the log-structured approach superior?
```sh
+ Direct: 
Logical Operation Sums
  Write count 520 (0 failed)
  Read count  374 (0 failed)
  Trim count  106 (0 failed)

Times
  Erase time 520000.00
  Write time 188960.00
  Read time  50480.00
  Total time 759440.00
 
+ Log:
Logical Operation Sums
  Write count 520 (450 failed)
  Read count  374 (209 failed)
  Trim count  106 (67 failed)

Times
  Erase time 7000.00
  Write time 2800.00
  Read time  1650.00
  Total time 11450.00

+ Ideal:
Logical Operation Sums
  Write count 520 (0 failed)
  Read count  374 (0 failed)
  Trim count  106 (0 failed)

Times
  Erase time 0.00
  Write time 20800.00
  Read time  3740.00
  Total time 24540.00

```
9. One last aspect to explore is workload skew. Adding skew to the workload changes writes such that more writes occur to some smaller fraction of the logical block space. For example, running with -K 80/20 makes 80% of the writes go to 20% of the blocks. Pick some different skews and perform many randomly-chosen operations (e.g., -n 1000), using first-T direct to understand the skew, and then -T log to see the impact on a log-structured device. What do you expect will happen? One other small skew control to explore is -k 100; by adding this flag to a skewed workload, the first 100 writes are not skewed. The idea is to first create a lot of data, but then only update some of it. What impact might that have upon a garbage collector?
```sh

```