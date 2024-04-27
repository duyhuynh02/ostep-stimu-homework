# Homework (Simulation)
## In this homework, we’ll use multi.py to simulate a multi-processor CPU scheduler, and learn about some of its details. Read the related README for more information about the simulator and its options.

```sh
prompt> ./multi.py -h
Usage: multi.py [options]

Options:
Options:
  -h, --help            show this help message and exit
  -s SEED, --seed=SEED  the random seed
  -j JOB_NUM, --job_num=JOB_NUM
                        number of jobs in the system
  -R MAX_RUN, --max_run=MAX_RUN
                        max run time of random-gen jobs
  -W MAX_WSET, --max_wset=MAX_WSET
                        max working set of random-gen jobs
  -L JOB_LIST, --job_list=JOB_LIST
                        provide a comma-separated list of
                        job_name:run_time:working_set_size (e.g.,
                        a:10:100,b:10:50 means 2 jobs with run-times of 10,
                        the first (a) with working set size=100, second (b)
                        with working set size=50)
  -p, --per_cpu_queues  per-CPU scheduling queues (not one)
  -A AFFINITY, --affinity=AFFINITY
                        a list of jobs and which CPUs they can run on (e.g.,
                        a:0.1.2,b:0.1 allows job a to run on CPUs 0,1,2 but b
                        only on CPUs 0 and 1
  -n NUM_CPUS, --num_cpus=NUM_CPUS
                        number of CPUs
  -q TIME_SLICE, --quantum=TIME_SLICE
                        length of time slice
  -P PEEK_INTERVAL, --peek_interval=PEEK_INTERVAL
                        for per-cpu scheduling, how often to peek at other
                        schedule queue; 0 turns this off
  -w WARMUP_TIME, --warmup_time=WARMUP_TIME
                        time it takes to warm cache
  -r WARM_RATE, --warm_rate=WARM_RATE
                        how much faster to run with warm cache
  -M CACHE_SIZE, --cache_size=CACHE_SIZE
                        cache size
  -o, --rand_order      has CPUs get jobs in random order
  -t, --trace           enable basic tracing (show which jobs got scheduled)
  -T, --trace_time_left
                        trace time left for each job
  -C, --trace_cache     trace cache status (warm/cold) too
  -S, --trace_sched     trace scheduler state
  -c, --compute         compute answers for me
```

### Questions
1. To start things off, let’s learn how to use the simulator to study how to build an effective multi-processor scheduler. The first simulation will run just one job, which has a run-time of 30, and a working-set size of 200. Run this job (called job ’a’ here) on one simulated CPU as follows: ./multi.py -n 1 -L a:30:200. How long will it take to complete? Turn on the -c flag to see a final answer, and the -t flag to see a tick-by-tick trace of the job and how it is scheduled.
```sh
Finished time 30

Per-CPU stats
  CPU 0  utilization 100.00 [ warm 0.00 ]
```
2. Now increase the cache size so as to make the job’s working set (size=200) fit into the cache (which, by default, is size=100); for example, run ./multi.py -n 1 -L a:30:200 -M 300. Can you predict how fast the job will run once it fits in cache? (hint: remember the key parameter of the warm rate, which is set by the -r flag) Check your answer by running with the solve flag (-c) enabled.
```sh
Finished time 20

Per-CPU stats
  CPU 0  utilization 100.00 [ warm 50.00 ]
```
3. One cool thing about multi.py is that you can see more detail about what is going on with different tracing flags. Run the same simulation as above, but this time with time left tracing enabled (-T). This flag shows both the job that was scheduled on a CPU at each time step, as well as how much run-time that job has left after each tick has run. What do you notice about how that second column decreases?
```sh
./multi.py -n 1 -L a:30:200 -M 300 -t -r 5 -T -c
```
4. Now add one more bit of tracing, to show the status of each CPU cache for each job, with the -C flag. For each job, each cache will either show a blank space (if the cache is cold for that job) or a ’w’ (if the cache is warm for that job). At what point does the cache become warm for job ’a’ in this simple example? What happens as you change the warmup time parameter (-w) to lower or higher values than the default?
```sh
The 9th working set. 
It will finish faster. 
```
5. At this point, you should have a good idea of how the simulator works for a single job running on a single CPU. But hey, isn’t this a multi-processor CPU scheduling chapter? Oh yeah! So let’s start working with multiple jobs. Specifically, let’s run the following three jobs on a two-CPU system (i.e., type ./multi.py -n 2 -L a:100:100,b:100:50,c:100:50) Can you predict how long this will take, given a round-robin centralized scheduler? Use -c to see if you were right, and then dive down into details with -t to see a step-by-step and then -C to see whether caches got warmed effectively for these jobs. What do you notice?
```sh
./multi.py -n 2 -L a:100:100,b:100:50,c:100:50 -c -T

```
6. Now we’ll apply some explicit controls to study cache affinity, as described in the chapter. To do this, you’ll need the -A flag. This flag can be used to limit which CPUs the scheduler can place a particular job upon. In this case, let’s use it to place jobs ’b’ and ’c’ on CPU 1, while restricting ’a’ to CPU 0. This magic is accomplished by typing this ./multi.py -n 2 -L a:100:100,b:100:50, c:100:50 -A a:0,b:1,c:1 ; don’t forget to turn on various tracing options to see what is really happening! Can you predict how fast this version will run? Why does it do better? Will other combinations of ’a’, ’b’, and ’c’ onto the two processors run faster or slower?
```sh
./multi.py -n 2 -L a:100:100,b:100:50,c:100:50 -A a:0,b:1,c:1 -t -T -C -c
Finished time 110

Per-CPU stats
  CPU 0  utilization 50.00 [ warm 40.91 ]
  CPU 1  utilization 100.00 [ warm 81.82 ]

It will be faster. 
```

7. One interesting aspect of caching multiprocessors is the opportunity for better-than-expected speed up of jobs when using multiple CPUs (and their caches) as compared to running jobs on a single processor. Specifically, when you run on N CPUs, sometimes you can speed up by more than a factor of N, a situation entitled super-linear speedup. To experiment with this, use the job description here (-L a:100:100 b:100:100,c:100:100) with a small cache (-M 50) to create three jobs. Run this on systems with 1, 2, and 3 CPUs (-n 1, -n 2, -n 3). Now, do the same, but with a larger per-CPU cache of size 100. What do you notice about performance as the number of CPUs scales? Use -c to confirm your guesses, and other tracing flags to dive even deeper.

```sh
./multi.py -n 1 -L a:100:100,b:100:100,c:100:100 -M 50 -t -T -C -c
Finished time 300

Per-CPU stats
  CPU 0  utilization 100.00 [ warm 0.00 ]

Compared to cache size 100 
Finished time 300

Per-CPU stats
  CPU 0  utilization 100.00 [ warm 0.00 ]  
```

```sh
./multi.py -n 2 -L a:100:100,b:100:100,c:100:100 -M 50 -t -T -C -c

Finished time 150

Per-CPU stats
  CPU 0  utilization 100.00 [ warm 0.00 ]
  CPU 1  utilization 100.00 [ warm 0.00 ]

And cache size 100 (-M 100 or default?)

Compared to -M 100:
Finished time 150

Per-CPU stats
  CPU 0  utilization 100.00 [ warm 0.00 ]
  CPU 1  utilization 100.00 [ warm 0.00 ]
```

```sh
./multi.py -n 3 -L a:100:100,b:100:100,c:100:100 -M 50 -t -T -C -c

Finished time 100

Per-CPU stats
  CPU 0  utilization 100.00 [ warm 0.00 ]
  CPU 1  utilization 100.00 [ warm 0.00 ]
  CPU 2  utilization 100.00 [ warm 0.00 ]

Compared to -M 100:
Finished time 55

Per-CPU stats
  CPU 0  utilization 100.00 [ warm 81.82 ]
  CPU 1  utilization 100.00 [ warm 81.82 ]
  CPU 2  utilization 100.00 [ warm 81.82 ]
```
8. One other aspect of the simulator worth studying is the per-CPU scheduling option, the -p flag. Run with two CPUs again, and this three job configuration (-L a:100:100,b:100:50,c:100:50). How does this option do, as opposed to the hand-controlled affinity limits you put in place above? How does performance change as you alter the ’peek interval’ (-P) to lower or higher values? How does this per-CPU approach work as the number of CPUs scales?
```sh
./multi.py -n 2 -L a:100:100,b:100:50,c:100:50 -t -p -T -C -c

Finished time 100

Per-CPU stats
  CPU 0  utilization 95.00 [ warm 35.00 ]
  CPU 1  utilization 95.00 [ warm 75.00 ]
```
9. Finally, feel free to just generate random workloads and see if you can predict their performance on different numbers of processors, cache sizes, and scheduling options. If you do this, you’ll soon be a multi-processor scheduling master, which is a pretty awesome thing to be. Good luck