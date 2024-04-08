# Homework (Code)

## In this homework, you will gain some familiarity with memory allocation. First, you’ll write some buggy programs (fun!). Then, you’ll use some tools to help you find the bugs you inserted. Then, you will realize how awesome these tools are and use them in the future, thus making yourself more happy and productive. The tools are the debugger (e.g., gdb) and a memory-bug detector called valgrind [SN05].

### Questions
1. First, write a simple program called null.c that creates a pointer to an integer, sets it to NULL, and then tries to dereference it. Compile this into an executable called null. What happens when you run this program?
```sh
Check ./null
Exception has occurred: Segmentation fault
```
2. Next, compile this program with symbol information included (with the -g flag). Doing so let’s put more information into the executable, enabling the debugger to access more useful information about variable names and the like. Run the program under the debugger by typing gdb null and then, once gdb is running, typing run. What does gdb show you?
```sh
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGSEGV, Segmentation fault.
0x0000555555555161 in main () at /home/xx/projects/xx/null.c:6
6           printf("Derefrencing the null pointer: %d\n", *ptr);

```
3. Finally, use the valgrind tool on this program. We’ll use memcheck that is a part of valgrind to analyze what happens. Run this by typing in the following: valgrind --leak-check=yes null. What happens when you run this? Can you interpret the output from the tool?
```sh
==92532== Memcheck, a memory error detector
==92532== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==92532== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==92532== Command: ./null
==92532==
==92532== Invalid read of size 4
==92532==    at 0x109161: main (null.c:6)
==92532==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==92532==
==92532==
==92532== Process terminating with default action of signal 11 (SIGSEGV)
==92532==  Access not within mapped region at address 0x0
==92532==    at 0x109161: main (null.c:6)
==92532==  If you believe this happened as a result of a stack
==92532==  overflow in your program's main thread (unlikely but
==92532==  possible), you can try to increase the size of the
==92532==  main thread stack using the --main-stacksize= flag.
==92532==  The main thread stack size used in this run was 8388608.
==92532==
==92532== HEAP SUMMARY:
==92532==     in use at exit: 0 bytes in 0 blocks
==92532==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==92532==
==92532== All heap blocks were freed -- no leaks are possible
==92532==
==92532== For lists of detected and suppressed errors, rerun with: -s
==92532== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

It summarize the memory allocation for stack and heap, and if we run with -s, it also gave us an error message, which is segmentation fault.
```
4. Write a simple program that allocates memory using malloc() but forgets to free it before exiting. What happens when this program runs? Can you use gdb to find any problems with it? How about valgrind (again with the --leak-check=yes flag)?
```sh
Using gdb: nothing happens 

Using valgrind: ~/projects/vm-api$ valgrind --leak-check=yes ./allocate 
==98524== HEAP SUMMARY:
==98524==     in use at exit: 28 bytes in 1 blocks
==98524==   total heap usage: 1 allocs, 0 frees, 28 bytes allocated
==98524==
==98524== 28 bytes in 1 blocks are definitely lost in loss record 1 of 1
==98524==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==98524==    by 0x10916C: main (allocate.c:9)
==98524==
==98524== LEAK SUMMARY:
==98524==    definitely lost: 28 bytes in 1 blocks
==98524==    indirectly lost: 0 bytes in 0 blocks
==98524==      possibly lost: 0 bytes in 0 blocks
==98524==    still reachable: 0 bytes in 0 blocks
==98524==         suppressed: 0 bytes in 0 blocks
==98524==
==98524== For lists of detected and suppressed errors, rerun with: -s
==98524== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

If we do not free the allocation, it could be lead to leaking memory if it's very big.
```
5. Write a program that creates an array of integers called data of size 100 using malloc; then, set data[100] to zero. What happens when you run this program? What happens when you run this program using valgrind? Is the program correct?
```sh
Nothing happens when I run.
When using valgrind: 
==102107== Invalid write of size 4
==102107==    at 0x10919B: main (assign.c:10)
==102107==  Address 0x4a8c1d0 is 0 bytes after a block of size 400 alloc'd
==102107==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==102107==    by 0x10918C: main (assign.c:9)
==102107==
==102107== Conditional jump or move depends on uninitialised value(s)
==102107==    at 0x48D6AD6: __vfprintf_internal (vfprintf-internal.c:1516)
==102107==    by 0x48C079E: printf (printf.c:33)
==102107==    by 0x1091C2: main (assign.c:12)
==102107==
==102107== Use of uninitialised value of size 8
==102107==    at 0x48BA2EB: _itoa_word (_itoa.c:177)
==102107==    by 0x48D5ABD: __vfprintf_internal (vfprintf-internal.c:1516)
==102107==    by 0x48C079E: printf (printf.c:33)
==102107==    by 0x1091C2: main (assign.c:12)
==102107==
==102107== Conditional jump or move depends on uninitialised value(s)
==102107==    at 0x48BA2FC: _itoa_word (_itoa.c:177)
==102107==    by 0x48D5ABD: __vfprintf_internal (vfprintf-internal.c:1516)
==102107==    by 0x48C079E: printf (printf.c:33)
==102107==    by 0x1091C2: main (assign.c:12)
==102107==
==102107== Conditional jump or move depends on uninitialised value(s)
==102107==    at 0x48D65C3: __vfprintf_internal (vfprintf-internal.c:1516)
==102107==    by 0x48C079E: printf (printf.c:33)
==102107==    by 0x1091C2: main (assign.c:12)
==102107==
==102107== Conditional jump or move depends on uninitialised value(s)
==102107==    at 0x48D5C05: __vfprintf_internal (vfprintf-internal.c:1516)
==102107==    by 0x48C079E: printf (printf.c:33)
==102107==    by 0x1091C2: main (assign.c:12)
==102107==
data[99] = 0
==102107== Invalid read of size 4
==102107==    at 0x1091CD: main (assign.c:13)
==102107==  Address 0x4a8c1d0 is 0 bytes after a block of size 400 alloc'd
==102107==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==102107==    by 0x10918C: main (assign.c:9)
==102107==
arr[100] = 0
==102107==
==102107== HEAP SUMMARY:
==102107==     in use at exit: 400 bytes in 1 blocks
==102107==   total heap usage: 2 allocs, 1 frees, 1,424 bytes allocated
==102107==
==102107== 400 bytes in 1 blocks are definitely lost in loss record 1 of 1
==102107==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==102107==    by 0x10918C: main (assign.c:9)
==102107==
==102107== LEAK SUMMARY:
==102107==    definitely lost: 400 bytes in 1 blocks
==102107==    indirectly lost: 0 bytes in 0 blocks
==102107==      possibly lost: 0 bytes in 0 blocks
==102107==    still reachable: 0 bytes in 0 blocks
==102107==         suppressed: 0 bytes in 0 blocks
==102107==
==102107== Use --track-origins=yes to see where uninitialised values come from
==102107== ERROR SUMMARY: 8 errors from 8 contexts (suppressed: 0 from 0)
==102107==
==102107== 1 errors in context 1 of 8:
==102107== Invalid read of size 4
==102107==    at 0x1091CD: main (assign.c:13)
==102107==  Address 0x4a8c1d0 is 0 bytes after a block of size 400 alloc'd
==102107==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==102107==    by 0x10918C: main (assign.c:9)
==102107==
==102107==
==102107== 1 errors in context 2 of 8:
==102107== Conditional jump or move depends on uninitialised value(s)
==102107==    at 0x48D5C05: __vfprintf_internal (vfprintf-internal.c:1516)
==102107==    by 0x48C079E: printf (printf.c:33)
==102107==    by 0x1091C2: main (assign.c:12)
==102107==
==102107==
==102107== 1 errors in context 3 of 8:
==102107== Conditional jump or move depends on uninitialised value(s)
==102107==    at 0x48D65C3: __vfprintf_internal (vfprintf-internal.c:1516)
==102107==    by 0x48C079E: printf (printf.c:33)
==102107==    by 0x1091C2: main (assign.c:12)
==102107==
==102107==
==102107== 1 errors in context 4 of 8:
==102107== Conditional jump or move depends on uninitialised value(s)
==102107==    at 0x48BA2FC: _itoa_word (_itoa.c:177)
==102107==    by 0x48D5ABD: __vfprintf_internal (vfprintf-internal.c:1516)
==102107==    by 0x48C079E: printf (printf.c:33)
==102107==    by 0x1091C2: main (assign.c:12)
==102107==
==102107==
==102107== 1 errors in context 5 of 8:
==102107== Use of uninitialised value of size 8
==102107==    at 0x48BA2EB: _itoa_word (_itoa.c:177)
==102107==    by 0x48D5ABD: __vfprintf_internal (vfprintf-internal.c:1516)
==102107==    by 0x48C079E: printf (printf.c:33)
==102107==    by 0x1091C2: main (assign.c:12)
==102107==
==102107==
==102107== 1 errors in context 6 of 8:
==102107== Conditional jump or move depends on uninitialised value(s)
==102107==    at 0x48D6AD6: __vfprintf_internal (vfprintf-internal.c:1516)
==102107==    by 0x48C079E: printf (printf.c:33)
==102107==    by 0x1091C2: main (assign.c:12)
==102107==
==102107==
==102107== 1 errors in context 7 of 8:
==102107== Invalid write of size 4
==102107==    at 0x10919B: main (assign.c:10)
==102107==  Address 0x4a8c1d0 is 0 bytes after a block of size 400 alloc'd
==102107==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==102107==    by 0x10918C: main (assign.c:9)
==102107==
==102107== ERROR SUMMARY: 8 errors from 8 contexts (suppressed: 0 from 0)

=> Accessing data[100] leads to undefined behavior, as it refers to memory beyond the allocated space.
```
6. Create a program that allocates an array of integers (as above), frees them, and then tries to print the value of one of the elements of the array. Does the program run? What happens when you use valgrind on it?
```sh
Same as %5, but change it to arr[99] 
==104237== HEAP SUMMARY:
==104237==     in use at exit: 0 bytes in 0 blocks
==104237==   total heap usage: 2 allocs, 2 frees, 1,424 bytes allocated
==104237==
==104237== All heap blocks were freed -- no leaks are possible
==104237==
==104237== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
7. Now pass a funny value to free (e.g., a pointer in the middle of the array you allocated above). What happens? Do you need tools to find this type of problem?
```sh
==104934== HEAP SUMMARY:
==104934==     in use at exit: 400 bytes in 1 blocks
==104934==   total heap usage: 2 allocs, 1 frees, 1,424 bytes allocated
==104934==
==104934== 400 bytes in 1 blocks are definitely lost in loss record 1 of 1
==104934==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==104934==    by 0x1091AC: main (assign.c:9)
==104934==
==104934== LEAK SUMMARY:
==104934==    definitely lost: 400 bytes in 1 blocks
==104934==    indirectly lost: 0 bytes in 0 blocks
==104934==      possibly lost: 0 bytes in 0 blocks
==104934==    still reachable: 0 bytes in 0 blocks
==104934==         suppressed: 0 bytes in 0 blocks
==104934==
==104934== Use --track-origins=yes to see where uninitialised values come from
==104934== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
==104934==
==104934== 1 errors in context 1 of 2:
==104934== Conditional jump or move depends on uninitialised value(s)
==104934==    at 0x484B235: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==104934==    by 0x1091F8: main (assign.c:15)
==104934==
==104934== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
```
8. Try out some of the other interfaces to memory allocation. For example, create a simple vector-like data structure and related routines that use realloc() to manage the vector. Use an array to store the vectors elements; when a user adds an entry to the vector, use realloc() to allocate more space for it. How well does such a vector perform? How does it compare to a linked list? Use valgrind to help you find bugs.
```sh
Check ./vector.c 
```
9. Spend more time and read about using gdb and valgrind. Knowing your tools is critical; spend the time and learn how to become an expert debugger in the UNIX and C environment.