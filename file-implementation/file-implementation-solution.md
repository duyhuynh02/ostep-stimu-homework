# HOMEWORK

## Use this tool, vsfs.py, to study how file system state changes as various operations take place. The file system begins in an empty state, with just a root directory. As the simulation takes place, various operations are performed, thus slowly changing the on-disk state of the file system. See the README for details.

###  Questions
1. Run the simulator with some different randomseeds(say 17, 18, 19, 20), and see if you can figure out which operations must have taken place between each state change.
```
$ ./vsfs.py -n 6 -s 17
$ ./vsfs.py -n 6 -s 18
$ ./vsfs.py -n 6 -s 19
$ ./vsfs.py -n 6 -s 20
```


2. Now do the same, using different random seeds (say 21, 22, 23, 24), except run with the-r flag, thus making you guess the state change while being shown the operation. What can you conclude about the inode and data-block allocation algorithms, in terms of which blocks they prefer to allocate?
```
Initial:
inode bitmap:   10000000
inodes          [d a:0 r:2][][][][][][][]
data bitmap     10000000
data            [(.,0) (..,0)][][][][][][][]


1. mkdir('/o')
inode bitmap:   11000000
inodes:         [d a:0 r:3][d a:1 r:2][][][][][][]
data bitmap:    11000000
data:           [(.,0) (..,0) (o,1)][(.,1) (..,0)][][][][][][]


2. creat('/b') 
inode bitmap:   11100000
inodes:         [d a:0 r:3][d a:1 r:2][f a:-1 r:1][][][][][]
data bitmap:    11000000
data:           [(.,0) (..,0) (o,1) (b,2)][(.,1) (..,0)][][][][][][]


3. creat("/o/q") 
inode bitmap:   11110000
inodes:         [d a:0 r:3][d a:1 r:2][f a:-1 r:1][f a:-1 r:1][][][][]
data bitmap:    11000000
data:           [(.,0) (..,0) (o,1) (b,2)] [(.,1) (..,0)] [(.,1) (..,0) (q,3)][][][][][]

And so on....
```


3. Now reduce the number of data blocks in the file system, to very low numbers (say two), and run the simulator for a hundred or so requests. What types of files end up in the file system in this highly constrained layout? What types of operations would fail?
```
When running a simulator with this command, we can see that the operation working is mkdir. Perhaps when create a large file is impossible, and link to another file.
$ ./vsfs.py -d 2 -n 10 -c

```

4. Now do the same, but with inodes. With very few inodes, what types of operations can succeed? Which will usually fail? What is the final state of the file system likely to be?
```
Same with #3 
```
