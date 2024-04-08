# Homework (Code)
## In this homework, we’ll just learn about a few useful tools to examine virtual memory usage on Linux-based systems. This will only be a brief hint at what is possible; you’ll have to dive deeper on your own to truly become an expert (as always!).
# Questions
1. The first Linux tool you should check out is the very simple tool free. First, type man free and read its entire manual page; it’s short, don’t worry!
```sh
~/projects/vm-intro$ man free
```
2. Now, run free, perhaps using some of the arguments that might be useful (e.g., -m, to display memory totals in megabytes). How much memory is in your system? How much is free? Do these numbers match your intuition?
```sh
               total        used        free      shared  buff/cache   available
Mem:            7617         767        6417           3         432        6620
Swap:           2048           0        2048

I'm using WSL (Ubuntu), so it could be take a half of my accual total physical memory (RAM) - 16GB in my system. 

The rest is fine, used, free, shared, swap space is also okay. 
```
3. Next, create a little program that uses a certain amount of memory, called memory-user.c. This program should take one commandline argument: the number of megabytes of memory it will use. When run, it should allocate an array, and constantly stream through the array, touching each entry. The program should do this indefinitely, or, perhaps, for a certain amount of time also specified at the command line.
```sh
Check program below: 
./memory-user 
```
4. Now, while running your memory-user program, also (in a different terminal window, but on the same machine) run the free tool. How do the memory usage totals change when your program is running? How about when you kill the memory-user program? Do the numbers match your expectations? Try this for different amounts of memory usage. What happens when you use really large amounts of memory?
```
It will consume a portion of memory while memory-user running. 
It will overflow and stop the computer 
```
5. Let’s try one more tool, known as pmap. Spend some time, and read the pmap manual page in detail.
```sh
~/projects/vm-intro$ man pmap
```
6. To use pmap, you have to know the process ID of the process you’re interested in. Thus, first run ps auxw to see a list of all processes; then, pick an interesting one, such as a browser. You can also use your memory-user program in this case (indeed, you can even have that program call getpid() and print out its PID for your convenience).
```sh
~/projects/vm-intro$ pmap 123 
```
7. Now run pmap on some of these processes, using various flags (like -X) to reveal many details about the process. What do you see? How many different entities make up a modern address space, as opposed to our simple conception of code/stack/heap?
```
Same as above
```
8. Finally, let’s run pmap on your memory-user program, with different amounts of used memory. What do you see here? Does the output from pmap match your expectations?
```sh
25025:   ./memory-user
0000563c6a0d6000      4K r---- memory-user
0000563c6a0d7000      4K r-x-- memory-user
0000563c6a0d8000      4K r---- memory-user
0000563c6a0d9000      4K r---- memory-user
0000563c6a0da000      4K rw--- memory-user
0000563c6ae86000    132K rw---   [ anon ]
00007f90c2b89000   4112K rw---   [ anon ]
00007f90c2f8d000    160K r---- libc.so.6
00007f90c2fb5000   1620K r-x-- libc.so.6
00007f90c314a000    352K r---- libc.so.6
00007f90c31a2000      4K ----- libc.so.6
00007f90c31a3000     16K r---- libc.so.6
00007f90c31a7000      8K rw--- libc.so.6
00007f90c31a9000     52K rw---   [ anon ]
00007f90c31bb000      8K rw---   [ anon ]
00007f90c31bd000      8K r---- ld-linux-x86-64.so.2
00007f90c31bf000    168K r-x-- ld-linux-x86-64.so.2
00007f90c31e9000     44K r---- ld-linux-x86-64.so.2
00007f90c31f5000      8K r---- ld-linux-x86-64.so.2
00007f90c31f7000      8K rw--- ld-linux-x86-64.so.2
00007ffe936ab000    132K rw---   [ stack ]
00007ffe937bf000     16K r----   [ anon ]
00007ffe937c3000      8K r-x--   [ anon ]
 total             6876K
```