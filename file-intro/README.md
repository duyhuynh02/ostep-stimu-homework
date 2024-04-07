1. Stat: Write your own version of the command line program stat, which simply calls the stat() system call on a given file or directory. 
Print out file size, number of blocks allocated, reference (link) count, and so forth. 
What is the link count of a directory, as the number of entries 
in the directory changes? Useful interface: stat(), naturally. 

2. List Files: Write a program that lists files in the given directory.
When called without any arguments, the program should just print
the file names. When invoked with the -l flag, the program should
print out information about each file, such as the owner, group, permissions, and other information obtained from the stat() system
call. The program should take one additional argument, which is
the directory to read, e.g., myls -l directory. If no directory is
given, the program should just use the current working directory.
Useful interfaces: stat(), opendir(), readdir(), getcwd().