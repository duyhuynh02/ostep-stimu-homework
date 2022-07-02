# Threads API 

## Homework (Code)
In this section, we’ll write some simple multi-threaded programs and use a specific tool, called helgrind, to find problems in these programs. Read the README in the homework download for details on how to build the programs and run helgrind.

### Questions
1. First build main-race.c. Examine the code so you can see the (hopefully obvious) data race in the code. Now run helgrind (by typing valgrind --tool=helgrind main-race) to see how it reports the race. Does it point to the right lines of code? What other information does it give to you?

```sh
Yes.
The address and the size.
```

2. What happens when you remove one of the offending lines of code? Now
add a lock around one of the updates to the shared variable, and then around
both. What does helgrind report in each of these cases?
```sh
ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
Possible data races 
ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

3. Now let’s look at main-deadlock.c. Examine the code. This code has a problem known as deadlock (which we discuss in much more depth in a forthcoming chapter). Can you see what problem it might have?