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

```
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
```
The INT n instruction generates a call to the interrupt or exception handler specified with the destination operand
=> (c) 
```
16.  Consider the following scheduling policy implemented by an OS, in which a user can set numerical
priorities for processes running in the system. The OS scheduler maintains all ready processes
in a strict priority queue. When the CPU is free, it extracts the ready process with the highest
priority (breaking ties arbitrarily), and runs it until the process blocks or terminates. Which of the
following statements is/are true about this scheduling policy?
3
(a) This scheduler is an example of a non-preemptive scheduling policy.
(b) This scheduling policy can result in the starvation of low priority processes.
(c) This scheduling policy guarantees fairness across all active processes.
(d) This scheduling policy guarantees lowest average turnaround time for all processes.
```
```

17.  Consider the following scheduling policy implemented by an OS. Every time a process is scheduled, the OS runs the process for a maximum of 10 milliseconds or until the process blocks or
terminates itself before 10 milliseconds. Subsequently, the OS moves on to the next ready process
in the list of processes in a round-robin fashion. Which of the following statements is/are true
about this scheduling policy?
(a) This policy cannot be efficiently implemented without hardware support for timer interrupts.
(b) This scheduler is an example of a non-preemptive scheduling policy.
(c) This scheduling policy can sometimes result in involuntary context switches.
(d) This scheduling policy prioritizes processes with shorter CPU burst times over processes that
run for long durations.
```
```

18.  Consider a process P that needs to save its CPU execution context (values of some CPU registers)
on some stack when it makes a function call or system call. Which of the following statements
is/are true?
(a) During a system call, when transitioning from user mode to kernel mode, the context of the
process is saved on its kernel stack.
(b) During a function call in user mode, the context of the process is saved on its user stack.
(c) During a function call in kernel mode, the context of the process is saved on its user stack.
(d) During a function call in kernel mode, the context of the process is saved on its kernel stack.
```
```
19.  Which of the following statements is/are true regarding how the trap instruction (e.g., int n in x86)
is invoked when a trap occurs in a system?
(a) When a user makes a system call, the trap instruction is invoked by the kernel code handling
the system call
(b) When a user makes a system call, the trap instruction is invoked by userspace code (e.g., user
program or a library)
(c) When an external I/O device raises an interrupt, the trap instruction is invoked by the device
driver handling the interrupt
(d) When an external I/O device raises an interrupt signaling the completion of an I/O request,
the trap instruction is invoked by the user process that raised the I/O request
```
```

20.  Which of the following statements is/are true about a context switch?
(a) A context switch from one process to another will happen every time a process moves from
user mode to kernel mode
(b) For preemptive schedulers, a trap of any kind always leads to a context switch
(c) A context switch will always occur when a process has made a blocking system call, irrespective of whether the scheduler is preemptive or not
(d) For non-preemptive schedulers, a process that is ready/willing to run will not be context
switched out
```

```