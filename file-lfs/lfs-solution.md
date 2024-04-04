# Homework(Simulation)
This section introduces lfs.py, a simple LFS simulator you can use to understand better how an LFS-based file system works. Read the README for details on how to run the simulator.
```sh
prompt> ./lfs.py -h
Usage: lfs.py [options]

Options:
  -h, --help            show this help message and exit
  -s SEED, --seed=SEED  the random seed
  -N, --no_force        Do not force checkpoint writes after updates
  -D, --use_disk_cr     use disk (maybe old) version of checkpoint region
  -c, --compute         compute answers for me
  -o, --show_operations
                        print out operations as they occur
  -i, --show_intermediate
                        print out state changes as they occur
  -e, --show_return_codes
                        show error/return codes
  -n NUM_COMMANDS, --num_commands=NUM_COMMANDS
                        generate N random commands
  -p PERCENTAGES, --percentages=PERCENTAGES
                        percent chance of:
                        createfile,writefile,createdir,rmfile,linkfile,sync
                        (example is c30,w30,d10,r20,l10,s0)
  -a INODE_POLICY, --allocation_policy=INODE_POLICY
                        inode allocation policy: "r" for "random" or "s" for
                        "sequential"
  -L COMMAND_LIST, --command_list=COMMAND_LIST
                        command list in format:
                        "cmd1,arg1,...,argN:cmd2,arg1,...,argN:... where cmds
                        are:c:createfile, d:createdir, r:delete, w:write,
                        l:link, s:syncformat: c,filepath d,dirpath r,filepath
                        w,filepath,offset,numblks l,srcpath,dstpath s
```
# Questions
1. Run ./lfs.py -n 3, perhaps varying the seed (-s). Can you figure out which commands were run to generate the final file system contents? Can you tell which order those commands were issued? Finally, can you determine the liveness of each block in the final file system state? Use -o to show which commands were run, and -c to show the liveness of the final file system state. How much harder does the task become for you as you increase the number of commands issued (i.e., change -n 3 to -n 5)?
```sh
Commands: 
Create file /ku3 
write into file /ku3 with offset = 7 and size = x \(the simulation is size = 4, but I don't get it, maybe the size is random?)
create file /qg9 

Liveliness:
Block 14, 13, 9, 8, 12, 11 and 0. 
```
2. If you find the above painful, you can help yourself a little bit by showing the set of updates caused by each specific command. To do so, run ./lfs.py -n 3 -i. Now see if it is easier to understand what each command must have been. Change the random seed to get different commands to interpret (e.g., -s 1, -s 2, -s 3, etc.).
```sh
$ ./lfs.py -n 3 -s 1 -i [-o and -c] 
$ ./lfs.py -n 3 -s 2 -i [-o and -c]
$ ./lfs.py -n 3 -s 3 -i [-o and -c]

ps: Shoudn't it be the first question?  
```

3. To further test your ability to figure out what updates are made to disk by each command, run the following: ./lfs.py -o -F -s 100 (and perhaps a few other random seeds). This just shows a set of commands and does NOT show you the final state of the file system. Can you reason about what the final state of the file system must be?
```sh
$ ./lfs.py -o -F -s 100 
```
4. Now see if you can determine which files and directories are live after a number of file and directory operations. Run tt ./lfs.py -n 20 -s 1 and then examine the final file system state. Can you figure out which pathnames are valid? Run tt ./lfs.py -n 20 -s 1 -c -v to see the results. Run with -o to see if your answers match up given the series of random commands. Use different random seeds to get more problems.
```sh
Directory: ln7
Files: lt0, af4, oy3, ln7/zp3, ln7/zu5
```
5. Now let’s issue some specific commands. First, let’s create a file and write to it repeatedly. To do so, use the -L flag, which lets you specify specific commands to execute. Let’s create the file ”/foo” and write to it four times: -L c,/foo:w,/foo,0,1:w,/foo,1,1:w,/foo,2,1:w,/foo,3,1 -o. See if you can determine the liveness of the final file system state; use -c to check your answers.
```sh
Liveliness:
Block: 0, 19, 5, 4, 18, 8, 11, 14, 17
```
6. Now, let’s do the same thing, but with a single write operation instead of four. Run ./lfs.py -o -L c,/foo:w,/foo,0,4 to create file ”/foo” and write 4 blocks with a single write operation. Compute the liveness again, and check if you are right with -c. What is the main difference between writing a file all at once (as we do here) versus doing it one block at a time (as above)? What does this tell you about the importance of buffering updates in main memory as the real LFS does?
```sh
The block is continuous. In this example: 
$ ./lfs.py -o -L c,/foo:w,/foo,0,4

We can see the liveliness resides in block 8, 9, 10, 11, compared to the above, the block resides random address on the disk. 
```
7. Let’s do another specific example. First, run the following: ./lfs.py -L c,/foo:w,/foo,0,1. What does this set of commands do? Now, run ./lfs.py -L c,/foo:w,/foo,7,1. What does this set of commands do? How are the two different? What can you tell about the size field in the inode from these two sets of commands?
```sh
./lfs.py -L c,/foo:w,/foo,0,1
Create a file foo from root with /foo 
Write foo with offset = 0 and number of blocks = 1 

and
./lfs.py -L c,/foo:w,/foo,7,1
Create a file foo from root with /foo
Write foo with offset = 7 and number of blocks = 1 

The size is 1. 
```
8. Now let’s look explicitly at file creation versus directory creation. Run simulations ./lfs.py -L c,/foo and ./lfs.py -L d,/foo to create a file and then a directory. What is similar about these runs, and what is different?
```sh
Maybe it does not show linking? Not sure about this one. 
```
9. The LFS simulator supports hard links as well. Run the following to study how they work: ./lfs.py -L c,/foo:l,/foo,/bar:l,/foo,/goo -o -i. What blocks are written out when a hard link is created? How is this similar to just creating a new file, and how is it different? How does the reference count field change as links are created?
```sh
Link file point to the same inode and data block 
It increases 1 for each new link, the same with create new file? 

```
10. LFS makes many different policy decisions. We do not explore many of them here – perhaps something left for the future – but here is a simple one we do explore: the choice of inode number. First, run ./lfs.py -p c100 -n 10 -o -a s to show the usual behavior with the ”sequential” allocation policy, which tries to use free inode numbers nearest to zero. Then, change to a ”random” policy by running ./lfs.py -p c100 -n 10 -o -a r (the -p c100 flag ensures 100 percent of the random operations are file creations). What on-disk differences does a random policy versus a sequential policy result in? What does this say about the importance of choosing inode numbers in a real LFS?
```sh
Nearly 30% of the difference (53 compared to 43)
```
11. One last thing we’ve been assuming is that the LFS simulator always updates the checkpoint region after each update. In the real LFS, that isn’t the case: it is updated periodically to avoid long seeks. Run ./lfs.py -N -i -o -s 1000 to see some operations and the intermediate and final states of the file system when the checkpoint region isn’t forced to disk. What would happen if the checkpoint region is never updated? What if it is updated periodically? Could you figure out how to recover the file system to the latest state by rolling forward in the log?
```sh
It will rely on the log to recover the file system in the event of crash or failure => every time the system boots up, it would need to replay the entire log from the beginning to reconstruct the file system's state. Think of it as if you want to find "a jean" in your room, but you need to find all the building to find it. 

Instead of it, updating periodcally will help to minimize the time for seeking and improving the system performance. 
```