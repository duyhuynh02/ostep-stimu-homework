# Homework (Code)
## In this homework, you are to gain some familiarity with the process management APIs about which you just read. Don’t worry – it’s even more fun than it sounds! You’ll in general be much better off if you find as much time as you can to write some code, so why not start now?

### Questions
1. Write a program that calls fork(). Before calling fork(), have the main process access a variable (e.g., x) and set its value to something (e.g., 100). What value is the variable in the child process? What happens to the variable when both the child and parent change the value of x?
```sh
./p1 
Value of the first in the child process: 10
Value when both the child and parent change the value of x followed by the assigned value in child process. (e.g., in my program, it would be 11) 
```
2. Write a program that opens a file (with the open() system call) and then calls fork() to create a new process. Can both the child and parent access the file descriptor returned by open()? What happens when they are writing to the file concurrently, i.e., at the same time?
```sh
./p2 
Yes, both the child and parent can access the fd. 
Both child and parent will write concurrently, no matter what orders. 
```
3. Write another program using fork(). The child process should print “hello”; the parent process should print “goodbye”. You should try to ensure that the child process always prints first; can you do this without calling wait() in the parent?\
```sh
Maybe using Inter-Process Communication (IPC). Check my code p3. I'm using pipe system call, check it here: https://www.geeksforgeeks.org/pipe-system-call/ 

Maybe later, cannot guess it right :D 
```
4. Write a program that calls fork() and then calls some form of exec() to run the program /bin/ls. See if you can try all of the variants of exec(), including (on Linux) execl(), execle(), execlp(), execv(), execvp(), and execvpe(). Why do you think there are so many variants of the same basic call?
```sh
Check ./p4 
```
5. Now write a program that uses wait() to wait for the child process to finish in the parent. What does wait() return? What happens if you use wait() in the child?
```sh 
Check ./p5
Then child process will be done after parent success, and the wait will return -1. 
```
6. Write a slight modification of the previous program, this time using waitpid() instead of wait(). When would waitpid() be useful?
```sh
Documentation: waitpid() lets us specify what child process to wait for => so if you want to be more specific about one child, or multiple children, this is the case where waitpid() be useful. 
```
7. Write a program that creates a child process, and then in the child closes standard output (STDOUT FILENO). What happens if the child calls printf() to print some output after closing the descriptor?
```sh
it won't print 
```
8. Write a program that creates two children, and connects the standard output of one to the standard input of the other, using the pipe() system call.
```sh
Same with p3, will (i hope) come back later. 
```