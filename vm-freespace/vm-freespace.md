# VM-Freespace 

## Homework (Simulation)
The program, malloc.py, lets you explore the behavior of a simple
free-space allocator as described in the chapter. See the README for
details of its basic operation

### Questions and Answer 
1. First run with the flags -n 10 -H 0 -p BEST -s 0 to generate a few random allocations and frees. - - Can you predict what alloc()/free() will return? 
- Can you guess the state of the free list after each request? 
- What do you notice about the free list over time? -> It will grow over time. 
```sh
ptr[0] = Alloc(3) -> returned 1000 
List?  -> FreeList [Size 1]: [addr: 1003 size: 97];

Free(ptr[0]) 
returned ? -> 0 (-> means success)
List?   -> FreeList [Size 2]: [addr: 1000 size: 3], [addr: 1003 size: 97];

ptr[1] = Alloc(5) -> returned 1003 (search 2 elements);
List? -> FreeList [Size 3]: [addr: 1000 size: 3] [addr: 1008 size: 92];

Free(ptr[1])
returned ? -> returned 0 
List? -> FreeList [Size 3]: [addr: 1000 size: 3], [addr: 1003 size: 5], [addr: 1008 size: 92];

ptr[2] = Alloc(8) -> returned 1008 (search 3 elements);
List? -> FreeList [Size 3]: [addr: 1000 size: 3], [addr: 1003 size: 5], [addr: 1016 size: 84];

Free(ptr[2])
returned ? -> returned 0 
List?  -> FreeList [Size 4]: [addr: 1000 size: 3], [addr: 1003 size: 5], [addr: 1008 size: 8]; [addr: 1016 size: 84];

ptr[3] = Alloc(8) -> returned 1008 
List? -> FreeList [Size 3]: [addr: 1000 size: 3], [addr: 1003 size: 5], [addr: 1016 size: 84];

Free(ptr[3])
returned -> returned 0 
List? -> FreeList [Size 4]: [addr: 1000 size: 3], [addr: 1003 size: 5], [addr: 1008 size: 8]; [addr: 1016 size: 84];

ptr[4] = Alloc(2) -> returned 1000 
List? FreeList [Size 5]: [addr: 1002 size 1], [addr: 1003 size: 5], [addr: 1008 size: 8]; [addr: 1016 size: 84];

ptr[5] = Alloc(7) -> returned 1008; 
List? -> [addr: 1002 size 1], [addr: 1003 size: 5], [addr: 1015 size: 1], [addr: 1016 size: 84];
```

2. How are the results different when using a WORST fit policy to
search the free list (-p WORST)? What changes? -> FreeList growing faster when using WORSTFIT.
```sh
ptr[0] = Alloc(3) -> returned 1000 
List? -> [addr: 1003 size: 97]; 

Free(ptr[0])
returned -> 0 
List? -> [addr: 1000 size: 3], [addr: 1003 size: 97];

ptr[1] = Alloc(5) -> returned 1003 
List? -> [addr: 1000 size: 3], [addr: 1008 size: 92];

Free(ptr[1]) 
returned -> 0 
List? -> [addr: 1000 size: 3], [addr: 1003 size 5], [addr: 1008: size 92];

ptr[2] = Alloc(8) returned 1008 
List? [addr: 1000 size: 3 ], [addr: 1003 size: 5 ], [addr: 1016 size: 84];

Free(ptr[2])
returned -> 0 
List? [addr: 1000 size: 3 ], [addr: 1003 size: 5 ], [addr: 1008 size: 8]; [addr: 1016 size: 84];

ptr[3] = Alloc(8) returned 1016 
List? [addr: 1000 size: 3 ], [addr: 1003 size: 5 ], [addr: 1008 size: 8]; [addr: 1024 size: 76];

Free(ptr[3]) 
returned -> 0 
List? [addr: 1000 size: 3 ], [addr: 1003 size: 5 ], [addr: 1008 size: 8]; [addr: 1016 size: 8]; [addr: 1024 size: 76];

Same for the rest... I will not do it... 

ptr[4] = Alloc(2) returned ?
List? 

ptr[5] = Alloc(7) returned ?
List? 
```

3. What about when using FIRST fit (-p FIRST)? 
What speeds upwhen you use first fit? -> You don't have to go all the FreeList to -> reduce the time to alloc the size. 
```sh
ptr[0] = Alloc(3) returned 1000 (searched 1 elements)
Free List [ Size 1 ]: [ addr:1003 sz:97 ]

Free(ptr[0])
returned 0
Free List [ Size 2 ]: [ addr:1000 sz:3 ][ addr:1003 sz:97 ]

ptr[1] = Alloc(5) returned 1003 (searched 2 elements)
Free List [ Size 2 ]: [ addr:1000 sz:3 ][ addr:1008 sz:92 ]

Free(ptr[1])
returned 0
Free List [ Size 3 ]: [ addr:1000 sz:3 ][ addr:1003 sz:5 ][ addr:1008 sz:92 ]

ptr[2] = Alloc(8) returned 1008 (searched 3 elements)
Free List [ Size 3 ]: [ addr:1000 sz:3 ][ addr:1003 sz:5 ][ addr:1016 sz:84 ]

Free(ptr[2])
returned 0
Free List [ Size 4 ]: [ addr:1000 sz:3 ][ addr:1003 sz:5 ][ addr:1008 sz:8 ][ addr:1016 sz:84 ]

ptr[3] = Alloc(8) returned 1008 (searched 3 elements)
Free List [ Size 3 ]: [ addr:1000 sz:3 ][ addr:1003 sz:5 ][ addr:1016 sz:84 ]

Free(ptr[3])
returned 0
Free List [ Size 4 ]: [ addr:1000 sz:3 ][ addr:1003 sz:5 ][ addr:1008 sz:8 ][ addr:1016 sz:84 ]

ptr[4] = Alloc(2) returned 1000 (searched 1 elements)
Free List [ Size 4 ]: [ addr:1002 sz:1 ][ addr:1003 sz:5 ][ addr:1008 sz:8 ][ addr:1016 sz:84 ]

ptr[5] = Alloc(7) returned 1008 (searched 3 elements)
Free List [ Size 4 ]: [ addr:1002 sz:1 ][ addr:1003 sz:5 ][ addr:1015 sz:1 ][ addr:1016 sz:84 ]

```

4. For the above questions, how the list is kept ordered can affect the
time it takes to find a free location for some of the policies. Use
the different free list orderings (-l ADDRSORT, -l SIZESORT+,
-l SIZESORT-) to see how the policies and the list orderings interact.
```sh
Depend on the size or the address, it sorted as the following order. 
```

5. Coalescing of a free list can be quite important. Increase the number
of random allocations (say to -n 1000).
- What happens to larger allocation requests over time? Run with and without coalescing
(i.e., without and with the -C flag). What differences in outcome do you see? 
```sh 
The freeList become larger over time and will need time to go through all to find the suitable 
address (allocation) to address. 
Check the command: ./malloc.py -n 10 -H 0 -p BEST -s 0 -n 1000 -C -c
```

Does the ordering of the list matter in this case?
```sh 
It will depend on the type of policy we choose. 
```

6. What happens when you change the percent allocated fraction -P
to higher than 50? What happens to allocations as it nears 100?
What about as the percent nears 0?
```sh
When change the percent allocated fraction nearly 100: the freeList become small, almost just one freeLIst or none to allocate at a time.
The opposite when the percent nears 0. 
./malloc.py -n 10 -H 0 -p BEST -s 0 -n 1000 -P 100 -c
./malloc.py -n 10 -H 0 -p BEST -s 0 -n 1000 -P 1 -c
```

7. What kind of specific requests can you make to generate a highlyfragmented free space? Use the -A flag to create fragmented free
lists, and see how different policies and options change the organization of the free list
```sh
Anything you want... 
```
