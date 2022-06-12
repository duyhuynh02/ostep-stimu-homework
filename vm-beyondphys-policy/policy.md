# Chapter 21: VM Beyond Physical - Policy 

## HOMEWORK (Simulation)
This simulator, paging-policy.py, allows you to play around with different page-replacement policies. See the README for details.

### Questions and Answers 
1. Generate random addresses with the following arguments: -s 0 -n 10, -s 1 -n 10, and -s 2 -n 10. Change the policy from FIFO, to LRU, to OPT. Compute whether each access in said address traces are hits or misses.
```sh
./paging-policy.py -s 0 -n 10 -p FIFO -c => Hit rate = 10% 
./paging-policy.py -s 1 -n 10 -p FIFO -c => 20% 
./paging-policy.py -s 2 -n 10 -p FIFO -c => 40% 

./paging-policy.py -s 0 -n 10 -p LRU -c => 20% 
./paging-policy.py -s 1 -n 10 -p LRU -c => 20% 
./paging-policy.py -s 2 -n 10 -p LRU -c => 40% 

./paging-policy.py -s 0 -n 10 -p OPT -c => 40% 
./paging-policy.py -s 1 -n 10 -p OPT -c => 30% 
./paging-policy.py -s 2 -n 10 -p OPT -c => 40% 
```
2. For a cache of size 5, generate worst-case address reference streams for each of the following policies: FIFO, LRU, and MRU (worst-case reference streams cause the most misses possible. For the worst case reference streams, how much bigger of a cache is needed to improve performance dramatically and approach OPT?
```sh
./paging-policy.py --addresses=0,1,2,3,4,5,0,1,2,3,4,5 --policy=FIFO --cachesize=5 -c
./paging-policy.py --addresses=0,1,2,3,4,5,0,1,2,3,4,5 --policy=LRU --cachesize=5 -c
./paging-policy.py --addresses=0,1,2,3,4,5,4,5,4,5,4,5 --policy=MRU --cachesize=5 -c

=> Just one is enough, cachesize = 6. 
```

3. Generate a random trace (use python or perl). How would you expect the different policies to perform on such a trace?
```sh
Just like question 1. 
```

4. Now generate a trace with some locality. How can you generate such a trace? How does LRU perform on it? How much better than RAND is LRU? How does CLOCK do? How about CLOCK with
different numbers of clock bits?
```sh
Locality: [3, 1, 4, 0, 2, 1, 9, 5, 0]
./paging-policy.py -a 3,1,4,0,2,1,9,5,0 -p FIFO -c 
FINALSTATS hits 0   misses 9   hitrate 0.00

./paging-policy.py -a 3,1,4,0,2,1,9,5,0 -p LRU -c 
FINALSTATS hits 0   misses 9   hitrate 0.00

./paging-policy.py -a 3,1,4,0,2,1,9,5,0 -p RAND -c 
FINALSTATS hits 1   misses 8   hitrate 11.11

./paging-policy.py -a 3,1,4,0,2,1,9,5,0 -p RAND -c -b 1
./paging-policy.py -a 3,1,4,0,2,1,9,5,0 -p RAND -c -b 2
./paging-policy.py -a 3,1,4,0,2,1,9,5,0 -p RAND -c -b 2
```

5. Use a program like valgrind to instrument a real application and
generate a virtual page reference stream. For example, running
valgrind --tool=lackey --trace-mem=yes ls will output
a nearly-complete reference trace of every instruction and data reference made by the program ls. To make this useful for the simulator above, you’ll have to first transform each virtual memory
reference into a virtual page-number reference (done by masking
off the offset and shifting the resulting bits downward). How big
of a cache is needed for your application trace in order to satisfy a
large fraction of requests? Plot a graph of its working set as the size
of the cache increases.
```sh
Do later... I hope so... 
```