# Process 

## Homework (Simulation)

This exercise is coming from 

### Questions 
1. Answer yes/no, and provide a brief explanation.
2. 
(a) Can two processes be concurrently executing the same program executable?

(b) Can two running processes share the complete process image in physical memory (not just
parts of it)?
```
(a) - Yes, two processes (or more) can run the same program.
(b) - No 
```

2. Consider a process executing on a CPU. Give an example scenario that can cause the process to
undergo:

(a) A voluntary context switch.

(b) An involuntary context switch.
```
(a) - A blocking system call 
(b) - Time interrupt that cause the process to be switched out 
```

3. Consider a parent process P that has forked a child process C. Now, P terminates while C is still
running. Answer yes/no, and provide a brief explanation.

(a) Will C immediately become a zombie?

(b) Will P immediately become a zombie, until reaped by its parent?
```
(a) - No, it will be adopted by init
(b) - Yes
```

4. A process in user mode cannot execute certain privileged hardware instructions. [T/F]
```
True - thats why they seperated between kernel mode and user mode. 
```

5. Which of the following C library functions do NOT directly correspond to (similarly named) system calls? That is, the implentations of which of these C library functions are NOT straightforward
invocations of the underlying system call?

(a) system, which executes a bash shell command.

(b) fork, which creates a new child process.

(c) exit, which terminates the current process.

(d) strlen, which returns the length of a string.
```
(a) & (d) 
```

6. Which of the following actions by a running process will always result in a context switch of the
running process, even in a non-preemptive kernel design?

(a) Servicing a disk interrupt, that results in another blocked process being marked as ready/runnable.

(b) A blocking system call.

(c) The system call exit, to terminate the current process.

(d) Servicing a timer interrupt.
```
(b) & (c) 
```

7. Consider two machines A and B of different architectures, running two different operating systems
OS-A and OS-B. Both operating systems are POSIX compliant. The source code of an application
that is written to run on machine A must always be rewritten to run on machine B. [T/F]
```
False - both two are written in POSIX compliant (Portable OS Interface)
```

8. Consider the scenario of the previous question. An application binary that has been compiled for
machine A may have to be recompiled to execute correctly on machine B. [T/F]
```
True. Althought the code is in POSIX compliant, the CPU instructions may different in compiling across different CPU architectures. 
```

9. A process makes a system call to read a packet from the network device, and blocks. The scheduler
then context-switches this process out. Is this an example of a voluntary context switch or an
involuntary context switch?
```
By blocking system call then it's a voluntary context switch.
```

10.  A context switch can occur only after processing a timer interrupt, but not after any other system
call or interrupt. [T/F]
```
False. Blocking system call can do it. 
```

11. A C program cannot directly invoke the OS system calls and must always use the C library for this
purpose. [T/F]
```
False. 
```

12.  A process undergoes a context switch every time it enters kernel mode from user mode. [T/F]
```
False. System can decide whether staying or change to user mode depends on what it needs. 

```
13. Consider a process P in xv6 that invokes the wait system call. Which of the following statements
is/are true?

(a) If P does not have any zombie children, then the wait system call returns immediately.

(b) The wait system call always blocks process P and leads to a context switch.

(c) If P has exactly one child process, and that child has not yet terminated, then the wait system
call will cause process P to block.

(d) If P has two or more zombie children, then the wait system call reaps all the zombie children
of P and returns immediately.
```
(c) When the parent process calls wait(), after the creation of a child, it indicates that, it will wait for the child to complete and it will reap the exit status of the child. The parent process is suspended(waits in a waiting queue) until the child is terminated. It must be understood that during this period, the parent process does nothing just wait.
```

14.  Consider a process P that executes the fork system call twice. That is, it runs code like this:
int ret1 = fork(); int ret2 = fork();
How many direct children of P (i.e., processes whose parent is P) and how many other descendants
of P (i.e., processes who are not direct children of P, but whose grandparent or great grandparent
or some such ancestor is P) are created by the above lines of code? You may assume that all fork
system calls succeed.

(a) Two direct children of P are created.

(b) Four direct children of P are created.

(c) No other descendant of P is created.

(d) One other descendant of P is created.

```sh
(a) & (d)
-------------------
    (p0)
   /    \  
(p1)    (p2)
  | 
 (p3)
```

15.  Consider the x86 instruction“int n” that is executed by the CPU to handle a trap. Which of the
following statements is/are true?

(a) This instruction is always invoked by privileged OS code.

(b) This instruction causes the CPU to set its EIP to address value “n”.

(c) This instruction causes the CPU to lookup the Interrupt Descriptor Table (IDT) using the
value “n” as an index.

(d) This instruction is always executed by the CPU only in response to interrupts from external
hardware, and never due to any code executed by the user.
```sh
The INT n instruction generates a call to the interrupt or exception handler specified with the destination operand
=> (c) 
```
16.  Consider the following scheduling policy implemented by an OS, in which a user can set numerical
priorities for processes running in the system. The OS scheduler maintains all ready processes
in a strict priority queue. When the CPU is free, it extracts the ready process with the highest
priority (breaking ties arbitrarily), and runs it until the process blocks or terminates. Which of the
following statements is/are true about this scheduling policy?
(a) This scheduler is an example of a non-preemptive scheduling policy.
(b) This scheduling policy can result in the starvation of low priority processes.
(c) This scheduling policy guarantees fairness across all active processes.
(d) This scheduling policy guarantees lowest average turnaround time for all processes.
```sh
(b)
```
> (a) and (b)

17.   Consider the following scheduling policy implemented by an OS. Every time a process is scheduled, the OS runs the process for a maximum of 10 milliseconds or until the process blocks or
terminates itself before 10 milliseconds. Subsequently, the OS moves on to the next ready process
in the list of processes in a round-robin fashion. Which of the following statements is/are true
about this scheduling policy?
(a) This policy cannot be efficiently implemented without hardware support for timer interrupts.
(b) This scheduler is an example of a non-preemptive scheduling policy.
(c) This scheduling policy can sometimes result in involuntary context switches.
(d) This scheduling policy prioritizes processes with shorter CPU burst times over processes that
run for long durations.
```sh
(c) (d)
```
> (a) (c)

18.   Consider a process P that needs to save its CPU execution context (values of some CPU registers)
on some stack when it makes a function call or system call. Which of the following statements
is/are true?
(a) During a system call, when transitioning from user mode to kernel mode, the context of the
process is saved on its kernel stack.
(b) During a function call in user mode, the context of the process is saved on its user stack.
(c) During a function call in kernel mode, the context of the process is saved on its user stack.
(d) During a function call in kernel mode, the context of the process is saved on its kernel stack.
```sh
(a), (b), (d)
```
> (a), (b), (d)

19.   Which of the following statements is/are true regarding how the trap instruction (e.g., int n in x86) is invoked when a trap occurs in a system?
(a) When a user makes a system call, the trap instruction is invoked by the kernel code handling
the system call
(b) When a user makes a system call, the trap instruction is invoked by userspace code (e.g., user
program or a library)
(c) When an external I/O device raises an interrupt, the trap instruction is invoked by the device
driver handling the interrupt
(d) When an external I/O device raises an interrupt signaling the completion of an I/O request,
the trap instruction is invoked by the user process that raised the I/O request
```sh
(a), (d)
```
> (b)

20.   Which of the following statements is/are true about a context switch?
(a) A context switch from one process to another will happen every time a process moves from
user mode to kernel mode
(b) For preemptive schedulers, a trap of any kind always leads to a context switch
(c) A context switch will always occur when a process has made a blocking system call, irrespective of whether the scheduler is preemptive or not
(d) For non-preemptive schedulers, a process that is ready/willing to run will not be context
switched out
```sh
(a), (c)
```
> (c), (d)

21. Consider the following C program. Assume there are no syntax errors and the program executes
correctly. Assume the fork system calls succeed. What is the output printed to the screen when
we execute the below program?
```c        
void main(argc, argv) {
  for(int i = 0; i < 4; i++) {
    int ret = fork();
    if(ret == 0)
    printf("child %d\n", i);
  }
}
```
Answer: 
```sh
child i will print 2^i from 0 to 3. 
```
> The statement “child i” is printed 2^i times for i=0 to 3

22. Consider a parent process P that has forked a child process C in the program below.
```c      
  int a = 5;
  int fd = open(...) //opening a file
  int ret = fork();
  if(ret >0) {
    close(fd);
    a = 6;
    ...
  }
  else if(ret==0) {
    printf("a=%d\n", a);
    read(fd, something);
  }
  ```
After the new process is forked, suppose that the parent process is scheduled first, before the child
process. Once the parent resumes after fork, it closes the file descriptor and changes the value of
a variable as shown above. Assume that the child process is scheduled for the first time only after
the parent completes these two changes.
(a) What is the value of the variable a as printed in the child process, when it is scheduled next?
Explain.
```sh 

```
(b) Will the attempt to read from the file descriptor succeed in the child? Explain.
```sh

```

23. Consider the following pseudocode. Assume all system calls succeed and there are no other errors
in the code.
```c
int ret1 = fork(); //fork1
int ret2 = fork(); //fork2
int ret3 = fork(); //fork3
wait();
wait();
wait();
```
Let us call the original parent process in this program as P. Draw/describe a family tree of P and
all its descendents (children, grand children, and so on) that are spawned during the execution of
this program. Your tree should be rooted at P. Show the spawned descendents as nodes in the tree,
and connect processes related by the parent-child relationship with an arrow from parent to child.
Give names of the form C¡number¿ for descendents, where child processes created by fork ”i”
above should have numbers like ”i1”, ”i2”, and so on. For example, child processes created by
fork3 above should have names C31, C32, and so on.
```sh

```

24. Consider a parent process that has forked a child in the code snippet below.
```c
int count = 0;
ret = fork();
if(ret == 0) {
  printf("count in child=%d\n", count);
}
else {
  count = 1;
}
```
The parent executes the statement ”count = 1” before the child executes for the first time. Now,
what is the value of count printed by the code above? Assume that the OS implements a simple
fork (not a copy-on-write fork).
```sh
0 
```
> Ans: 0 (the child has its own copy of the variable) 

25. Consider the wait family of system calls (wait, waitpid etc.) provided by Linux. A parent process
uses some variant of the wait system call to wait for a child that it has forked. Which of the
following statements is always true when the parent invokes the system call?
(a) The parent will always block.
(b) The parent will never block.
(c) The parent will always block if the child is still running.
(d) Whether the parent will block or not will depend on the system call variant and the options
with which it is invoked.
```sh
(c) (d)
```
> (d)

26. Consider a simple linux shell implementing the command sleep 100. Which of the following
is an accurate ordered list of system calls invoked by the shell from the time the user enters this
command to the time the shell comes back and asks the user for the next input?
(a) wait-exec-fork
(b) exec-wait-fork
(c) fork-exec-wait
(d) wait-fork-exec
```sh
(c)
```
> (c)

27. Consider a process P1 that forks P2, P2 forks P3, and P3 forks P4. P1 and P2 continue to execute
while P3 terminates. Now, when P4 terminates, which process must wait for and reap P4?
```sh

```


