# Scheduling: Scheduling Lottery 

## Homework (Simulation)

This program, lottery.py, allows you to see how a lottery scheduler
works. See the README for details.

### Questions 

1. Compute the solutions for simulations with 3 jobs and random seeds
of 1, 2, and 3.
```
./lottery.py -j 3 -s 1 -c
./lottery.py -j 3 -s 2 -c
./lottery.py -j 3 -s 3 -c
```

2. Now run with two specific jobs: each of length 10, but one (job 0)
with just 1 ticket and the other (job 1) with 100 (e.g., -l 10:1,10:100).
```
./lottery.py -m 10 -l 10:1,10:100 
```
What happens when the number of tickets is so imbalanced? Will job 0 ever run before job 1 completes? How often? 
```
To complete job 1 before job 0 run, we have around 100 tickets for job 1 and 1 ticket for job 0. 

That means, we choose (100 / 101) ^ 10 ~ 0.905 with 10 iterations in a row => Consequently, job 0 will have around 1 - 0.905 = 0.094 chance of running before job 1 finishes. 
```
In general, what does such a ticket imbalance do to the behavior of lottery scheduling?
```
Almost monopoly for job 1.
```


3. When running with two jobs of length 100 and equal ticket allocations of 100 (-l 100:100,100:100), how unfair is the scheduler?
Run with some different random seeds to determine the (probabilistic) answer; let unfairness be determined by how much earlier one job finishes than the other.
```
./lottery.py -j 2 -l 100:100,100:100 -c -s 1 
```
=> Unfairness Metric (UM) = 196 / 200 = 0.98 

```
./lottery.py -j 2 -l 100:100,100:100 -c -s 5
```
=> UM = 181 / 200 = 0.905 


4. How does your answer to the previous question change as the quantum size (-q) gets larger?
```
q-size  | unfairness
--------|------------
1       |   0.98
2       |   0.97
3       |   0.985
4       |   0.94
5       |   0.95
6       |   0.941
7       |   0.866
8       |   0.8846
9       |   0.8333
10      |   0.8
```
=> UM grows when increasing quantum size. 

5. Can you make a version of the graph that is found in the chapter?
What else would be worth exploring? How would the graph look
with a stride scheduler?
```
Will (maybe) comeback later
```