# HOMEWORK

## This section introduces raid.py, a simple RAID simulator you can use to shore up your knowledge of how RAID systems work. See the README for details.

###  Questions
1. Use the simulator to perform some basic RAID mapping tests. Run with different levels (0, 1, 4, 5) and see if you can figure out the mappings of a set of requests. For RAID-5, see if you can figure out the difference between left-symmetric and left-asymmetric layouts.
Use some different random seeds to generate different problems than above.
```
./raid.py -n 4 -R 20 -L 0 -c 
RAID level 0 -> disk = address % number_of_disks | offset = address / number_of_disks

./raid.py -n 4 -R 20 -L 1 -c 
RAID level 1 -> disk = ... | offset = address / 2 

./raid.py -n 4 -R 20 -L 4 -c 
RAID level 4 -> 

./raid.py -n 4 -R 20 -L 5 -c 
RAID level 5 -> 

```
2. Do the same as the first problem, but this time vary the chunk size with -C. How does chunk size change the mappings?
```
./raid.py -n 4 -R 20 -L 0 -C 8k -c 
./raid.py -n 4 -R 20 -L 1 -C 8k -c 
./raid.py -n 4 -R 20 -L 4 -C 8k -c 
./raid.py -n 4 -R 20 -L 5 -C 8k -c 
```
3. Do the same as above, but use the -r flag to reverse the nature of each problem.
```
./raid.py -n 4 -R 20 -L 0 -C 8k -r -c 
./raid.py -n 4 -R 20 -L 1 -C 8k -r -c 
./raid.py -n 4 -R 20 -L 4 -C 8k -r -c 
./raid.py -n 4 -R 20 -L 5 -C 8k -r -c 
```
4. Now use the reverse flag but increase the size of each request with the -S flag. Try specifying sizes of 8k, 12k, and 16k, while varying the RAID level. What happens to the underlying I/O pattern when the size of the request increases? Make sure to try this with the sequential workload too (-W sequential); for what request sizes are RAID-4 and RAID-5 much more I/O efficient?
```
$ ./raid.py -L 4 -S 4k -c -W seq
$ ./raid.py -L 4 -S 8k -c -W seq
$ ./raid.py -L 4 -S 12k -c -W seq
$ ./raid.py -L 4 -S 16k -c -W seq
$ ./raid.py -L 5 -S 4k -c -W seq
$ ./raid.py -L 5 -S 8k -c -W seq
$ ./raid.py -L 5 -S 12k -c -W seq
$ ./raid.py -L 5 -S 16k -c -W seq
```
5. Use the timing mode of the simulator (-t) to estimate the performance of 100 random reads to the RAID, while varying the RAID levels, using 4 disks.
```
./raid.py -L 0 -t -n 100 -c //275.69
./raid.py -L 1 -t -n 100 -c //278.7
./raid.py -L 4 -t -n 100 -c //386.1
./raid.py -L 5 -t -n 100 -c //276.7
```
6. Do the same as above, but increase the number of disks. How does the performance of each RAID level scale as the number of disks increases?
```
Number of disks default: 4 -> double to 8. 
./raid.py -L 0 -t -n 100 -D 8 -c //156.49 
./raid.py -L 1 -t -n 100 -D 8 -c //167,79 
./raid.py -L 4 -t -n 100 -D 8 -c //164.99
./raid.py -L 5 -t -n 100 -D 8 -c //158.59 
```
7. Do the same as above, but use all writes (-w 100) instead of reads. How does the performance of each RAID level scale now? Can you do a rough estimate of the time it will take to complete the workload of 100 random writes?
```
./raid.py -L 0 -t -n 100 -w 100 -c //275.69
./raid.py -L 1 -t -n 100 -w 100 -c //509.8
./raid.py -L 4 -t -n 100 -w 100 -c //982.5 
./raid.py -L 5 -t -n 100 -w 100 -c //498.4
```
8. Run the timing mode one last time, but this time with a sequenential workload (-W sequential). How does the performance vary with RAID level, and when doing reads versus writes? How about when varying the size of each request? What size should you write to a RAID when using RAID-4 or RAID-5?
```
./raid.py -L 0 -t -n 100 -w 100 -W seq -c //12.49 
./raid.py -L 1 -t -n 100 -w 100 -W seq -c //14.49
./raid.py -L 4 -t -n 100 -w 100 -W seq -c //13.39
./raid.py -L 5 -t -n 100 -w 100 -W seq -c //13.39

Whatever you choose is fine (RAID-4 and RAID-5).
Calculate the ratio by dividing read/write above. 
```