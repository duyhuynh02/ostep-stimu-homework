# Homework (Simulation)
## This section introduces fsck.py, a simple simulator you can use to better understand how file system corruptions can be detected (and potentially repaired). Please see the associated README for details on how to run the simulator.
```sh
prompt> ./fsck.py -h
Options:
  -h, --help            show this help message and exit
  -s SEED, --seed=SEED  first random seed (for a filesystem)
  -S SEEDCORRUPT, --seedCorrupt=SEEDCORRUPT
                        second random seed (for corruptions)
  -i NUMINODES, --numInodes=NUMINODES
                        number of inodes in file system
  -d NUMDATA, --numData=NUMDATA
                        number of data blocks in file system
  -n NUMREQUESTS, --numRequests=NUMREQUESTS
                        number of requests to simulate
  -p, --printFinal      print the final set of files/dirs
  -w WHICHCORRUPT, --whichCorrupt=WHICHCORRUPT
                        do a specific corruption
  -c, --compute         compute answers for me
  -D, --dontCorrupt     don't actually corrupt file system
```
### Questions
1. First, run fsck.py -D; this flag turns off any corruption, and thus
you can use it to generate a random file system, and see if you can
determine which files and directories are in there. So, go ahead and
do that! Use the -p flag to see if you were right. Try this for a few
different randomly-generated file systems by setting the seed (-s)
to different values, like 1, 2, and 3

```sh
dirs: ['/', '/g', '/w']
files: ['/m', '/z', 'g/s']

Same for -s 1, 2 or 3. 
```

2. Now, let’s introduce a corruption. Run fsck.py-S 1 to start. Can you see what inconsistency is introduced? How would you fix it in a real file system repair tool? Use-c to check if you were right.
```sh
Corruption happens in the bitmap 13. 
```

3. Change the seed to -S 3 or -S 19; which inconsistency do you see? Use -c to check your answer. What is different in these two cases?
```sh
./fsck.py -S 3 -> bitmap inode 15 is corrupted in reference, should be r:1, not 2. 

./fsck.py -S 19 -> bitmap inode 8 is corrupted in reference, should be r:2, not 1. 
```

4. Change the seed to -S 5; which inconsistency do you see? How
hard would it be to fix this problem in an automatic way? Use-c to
check your answer. Then, introduce a similar inconsistency with-S
38; is this harder/possible to detect? Finally, use-S 642; is this
inconsistency detectable? If so, how would you fix the file system?
```sh
With seed -S 5: No idea... Why does it change from y to s? 
With seed -S 642: Corruption in inode 4, entry ('..', 0) change to different name ('b', 0) 
```

5. Change the seed to -S 6 or -S 13; which inconsistency do you see? Use-c to check your answer. What is the difference across these two cases? What should the repair tool do when encountering such a situation?

```sh
./fsck.py -S 6 -> corruped in bitmap inode 12 
./fsck.py -S 13 -> same but with inode 10 
```

6. Change the seed to -S 9; which inconsistency do you see? Use -c
 to check your answer. Which piece of information should a check
and-repair tool trust in this case?
```sh
Inode 13 was type file, not directory. 
```

7. Change the seed to -S 15; which inconsistency do you see? Use-c to check your answer. What can a repair tool do in this case? If
 no repair is possible, how much data is lost?
 ```sh
Inode 0 is type directory, not file. 
All dirs '/g', '/w', and files '/m', '/z' can be lost.
 ```

 8. Change the seed to -S 10; which inconsistency do you see? Use -c to check your answer. Is there redundancy in the file system
 structure here that can help a repair?

 ```sh
Inode 4, should be [(.,4) (..,3)] 
 ```

 9. Change the seed to -S 16 and -S 20;which in consistency do you
 see? Use -c to check your answer. How should the repair tool fix
 the problem?
 ```sh
With -S 16 -> inode 13 should be [f a:-1 r:2]
With -S 20 -> inode 8 should be [d a:6 r:2]
 ```