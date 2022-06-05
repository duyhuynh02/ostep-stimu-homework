# VM-Smalltables 

## Homework (stimulation)
This fun little homework tests if you understand how a multi-level
page table works. And yes, there is some debate over the use of the term
“fun” in the previous sentence. The program is called, perhaps unsurprisingly: paging-multilevel-translate.py; see the README for
details.

### Questions
1. With a linear page table, you need a single register to locate the
page table, assuming that hardware does the lookup upon a TLB
miss. How many registers do you need to locate a two-level page
table? A three-level table?
```sh
One is enough, thats for PDBR. 
```

2. Use the simulator to perform translations given random seeds 0,
1, and 2, and check your answers using the -c flag. How many
memory references are needed to perform each lookup?

```sh
Just do one is enough... 
Lets do: ./paging-multilevel-translate.py
Here we have => PDBR: 108
-> choose page 108 ~ 
83(0th) fe e0 da 7f d4 7f eb be 9e d5 ad e4 ac 90 d6 92 d8 c1 f8 9f e1 ed e9 a1 e8 c7 c2 a9 d1 db ff

Virtual Address 611c: 011000(24th) 01000(8th) 11100(28) (PDE Index for 6 MSBs, PTE index for the next 5, the rest is offset)
-> pde index: 24th so the content is a1 which binary is 1(VALID)|0100001(33) => PFN = 33

Page 33: 
7f(0th) 7f 7f 7f 7f 7f 7f 7f b5 7f 9d 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f f6 b1 7f 7f 7f 7f
-> pte index: 8th so the content is b5 which binary is 1(VALID)|0110101(53) => PFN = 53

Page 53:
0f(0th) 0c 18 09 0e 12 1c 0f 08 17 13 07 1c 1e 19 1b 09 16 1b 15 0e 03 0d 12 1c 1d 0e 1a 08(28th) 18 11 00
-> translate to physical address: 0110101(53)11100(OFFSET=28) = 0x6bc => so the content is 08
```

3. Given your understanding of how cache memory works, how do
you think memory references to the page table will behave in the
cache? Will they lead to lots of cache hits (and thus fast accesses?)
Or lots of misses (and thus slow accesses)?
```sh
It's totally random so I guess it's a lot of misses. 
```