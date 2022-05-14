# Process 

## Homework (Simulation)

This exercise is coming from 

### Questions 
1. Answer yes/no, and provide a brief explanation.
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
