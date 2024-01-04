This homework uses disk.py to familiarize you with how a modern hard drive works. It has a lot of different options, and unlike most of 
the other simulations, has a graphical animator to show you exactly what happens when the disk is in action. See the README for details.

1. Compute the seek, rotation, and transfer times for the following sets of requests: -a 0, -a 6, -a 30, -a 7,30,8, and finally -a 10,11,12,13.
```
./disk.py -a 0 -G
seek time: 0 
rotate time: 165
transfer time: 30 
=> total: 210 time unit 
```

```
./disk.py -a 6 
seek time: 0 
rotate time: 345
transfer time: 30 
=> total: 375 time unit 
```
```
./disk.py -a 7,30,8 -G
seek time: 0 + 40 + 40 + 40 + 40 
rotate time: 15  + 220 + 310
transfer time: 30 + 30 + 30 
=> total: 795 time unit 
```

```
./disk.py -a 10,11,12,13
seek time: 0 + 0 + 40 + 0 
rotate time: 105 + 0 + 320 + 0
transfer time: 30 + 30 + 30 + 30 
=> total: 585 time unit 
```


2. Do the same requests above, but change the seek rate to different values: -S 2, -S 4, -S 8, -S 10, -S 40, -S 0.1. How do the times change?
```
Total is still the same, the only one has a difference is when you define -S 0.1, the seed decrease then the seek time increases. 
```
3. Do the same requests above, but change the rotation rate: -R 0.1, -R 0.5,
-R 0.01. How do the times change?
```
The time decrease significantly, it's easy to understand due to the speed rotation is too small comparing to the normal time unit.
```
4. FIFO is not always best, e.g., with the request stream -a 7,30,8, what order should the requests be processed in? Run the shortest seek-time first
(SSTF) scheduler (-p SSTF) on this workload; how long should it take
(seek, rotation, transfer) for each request to be served?
```
If we run normally (with FIFO):
Seek time: 160
Rorate time: 545 
Transfer time: 90
-> total: 795 

And if we run with SSTF: 
Seek time: 80
Rorate time: 205
Transfer time: 90
-> total: 375 

=> We need only 1/2 the time to complete the request. 
```
5. Now use the shortest access-time first (SATF) scheduler (-p SATF). Does it
make any difference for -a 7,30,8 workload? Find a set of requests where
SATF outperforms SSTF; more generally, when is SATF better than SSTF?
```
When we run with SATF: 
Seek time: 80
Rorate time: 205
Transfer time: 90
-> total: 375 

It's the same with seed 7, 30, and 8. 

SATF is better than SSTF when the rotational time is large compared to the seek time.  
$ ./disk.py -a 31,6 -c -p SATF -S 40 -R 1
$ ./disk.py -a 31,6 -c -p SSTF -S 40 -R 1
```
6. Here is a request stream to try: -a 10,11,12,13. What goes poorly when
it runs? Try adding track skew to address this problem (-o skew). Given
the default seek rate, what should the skew be to maximize performance?
What about for different seek rates (e.g., -S 2, -S 4)? In general, could
you write a formula to figure out the skew?
```
It bypassses the next sector (12) while during the rotation, therefore it increase the time nearly 360 time unit. 

./disk.py -a 10,11,12,13 -o 0 -G (by default we don't need to specify -o 0)
./disk.py -a 10,11,12,13 -o 2 -G
```
7. Specify a disk with different density per zone, e.g., -z 10,20,30, which
specifies the angular difference between blocks on the outer, middle, and
inner tracks. Run some random requests (e.g., -a -1 -A 5,-1,0, which
specifies that random requests should be used via the -a -1 flag and that
five requests ranging from 0 to the max be generated), and compute the
seek, rotation, and transfer times. Use different random seeds. What is the
bandwidth (in sectors per unit time) on the outer, middle, and inner tracks?
```

```
8. A scheduling window determines how many requests the disk can examine
at once. Generate random workloads (e.g., -A 1000,-1,0, with different
seeds) and see how long the SATF scheduler takes when the scheduling window is changed from 1 up to the number of requests. How big of a window
is needed to maximize performance? Hint: use the -c flag and don’t turn
on graphics (-G) to run these quickly. When the scheduling window is set
to 1, does it matter which policy you are using?
```
$ ./disk.py -A 1000,-1,0 -p SATF -w 1 -c      // 220125
$ ./disk.py -A 1000,-1,0 -p FIFO -w 1 -c      // 220125
$ ./disk.py -A 1000,-1,0 -p SSTF -w 1 -c      // 220125
$ ./disk.py -A 1000,-1,0 -p SATF -w 1000 -c   // 35475
```
9. Create a series of requests to starve a particular request, assuming an SATF
policy. Given that sequence, how does it perform if you use a bounded
SATF (BSATF) scheduling approach? In this approach, you specify the
scheduling window (e.g., -w 4); the scheduler only moves onto the next
window of requests when all requests in the current window have been serviced. Does this solve starvation? How does it perform, as compared to
SATF? In general, how should a disk make this trade-off between performance and starvation avoidance?
```

```
10. All the scheduling policies we have looked at thus far are greedy; they pick
the next best option instead of looking for an optimal schedule. Can you
find a set of requests in which greedy is not optimal?
```
$ ./disk.py -a 9,20 -c            // 435
$ ./disk.py -a 9,20 -c -p SATF    // 465
```