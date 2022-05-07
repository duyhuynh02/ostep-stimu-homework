1. 
Final statistics for FIFO: (length = 200) 
  Job   0 -- Response: 0.00  Turnaround 169.00  Wait 0.00
  Job   1 -- Response: 169.00  Turnaround 321.00  Wait 169.00
  Job   2 -- Response: 321.00  Turnaround 406.00  Wait 321.00

  Average -- Response: 163.33  Turnaround 298.67  Wait 163.33

-----------------------------------------------------------
Final statistics for SJF: 
  Job   2 -- Response: 0.00  Turnaround 85.00  Wait 0.00
  Job   1 -- Response: 85.00  Turnaround 237.00  Wait 85.00
  Job   0 -- Response: 237.00  Turnaround 406.00  Wait 237.00

  Average -- Response: 107.33  Turnaround 242.67  Wait 107.33

-----------------------------------------------------------

==> The response, turnaround, and the wait time for SJF is shorted than the FIFO algorithm. 

-----------------------------------------------------------

2. (length = 100) 
Here is the job list, with the run time of each job: 
  Job 0 ( length = 85 )
  Job 1 ( length = 76 )
  Job 2 ( length = 43 )
-----------------------------------------------------------
Solution for FIFO:
Execution trace:
  [ time   0 ] Run job 0 for 85.00 secs ( DONE at 85.00 )
  [ time  85 ] Run job 1 for 76.00 secs ( DONE at 161.00 )
  [ time 161 ] Run job 2 for 43.00 secs ( DONE at 204.00 )

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 85.00  Wait 0.00
  Job   1 -- Response: 85.00  Turnaround 161.00  Wait 85.00
  Job   2 -- Response: 161.00  Turnaround 204.00  Wait 161.00

  Average -- Response: 82.00  Turnaround 150.00  Wait 82.00

-----------------------------------------------------------
Solution for SJF:
Execution trace:
  [ time   0 ] Run job 2 for 43.00 secs ( DONE at 43.00 )
  [ time  43 ] Run job 1 for 76.00 secs ( DONE at 119.00 )
  [ time 119 ] Run job 0 for 85.00 secs ( DONE at 204.00 )

Final statistics:
  Job   2 -- Response: 0.00  Turnaround 43.00  Wait 0.00
  Job   1 -- Response: 43.00  Turnaround 119.00  Wait 43.00
  Job   0 -- Response: 119.00  Turnaround 204.00  Wait 119.00

  Average -- Response: 54.00  Turnaround 122.00  Wait 54.00

==> The response, turnaround, and the wait time still is shorter than the FIFO algorithm. 

-----------------------------------------------------------

3. (length = 300)
Here is the job list, with the run time of each job: 
  Job 0 ( length = 254 )
  Job 1 ( length = 228 )
  Job 2 ( length = 127 )
-------------
Solution for FIFO:
  [ time   0 ] Run job 0 for 254.00 secs ( DONE at 254.00 )
  [ time 254 ] Run job 1 for 228.00 secs ( DONE at 482.00 )
  [ time 482 ] Run job 2 for 127.00 secs ( DONE at 609.00 )

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 254.00  Wait 0.00
  Job   1 -- Response: 254.00  Turnaround 482.00  Wait 254.00
  Job   2 -- Response: 482.00  Turnaround 609.00  Wait 482.00

  Average -- Response: 245.33  Turnaround 448.33  Wait 245.33
----------------------------------
Solution for SJF:
  [ time   0 ] Run job 2 for 127.00 secs ( DONE at 127.00 )
  [ time 127 ] Run job 1 for 228.00 secs ( DONE at 355.00 )
  [ time 355 ] Run job 0 for 254.00 secs ( DONE at 609.00 )

Final statistics:
  Job   2 -- Response: 0.00  Turnaround 127.00  Wait 0.00
  Job   1 -- Response: 127.00  Turnaround 355.00  Wait 127.00
  Job   0 -- Response: 355.00  Turnaround 609.00  Wait 355.00

  Average -- Response: 160.67  Turnaround 363.67  Wait 160.67


======================================================================

3. Now do the same, but also with the RR scheduler and a time-slice
of 1.

For 100:
Final statistics:
  Job   0 -- Response: 0.00  Turnaround 204.00  Wait 119.00
  Job   1 -- Response: 1.00  Turnaround 195.00  Wait 119.00
  Job   2 -- Response: 2.00  Turnaround 129.00  Wait 86.00

  Average -- Response: 1.00  Turnaround 176.00  Wait 108.00

For 200:
Final statistics:
  Job   0 -- Response: 0.00  Turnaround 406.00  Wait 237.00
  Job   1 -- Response: 1.00  Turnaround 389.00  Wait 237.00
  Job   2 -- Response: 2.00  Turnaround 255.00  Wait 170.00

  Average -- Response: 1.00  Turnaround 350.00  Wait 214.67

For 300:
Final statistics:
  Job   0 -- Response: 0.00  Turnaround 609.00  Wait 355.00
  Job   1 -- Response: 1.00  Turnaround 583.00  Wait 355.00
  Job   2 -- Response: 2.00  Turnaround 381.00  Wait 254.00

  Average -- Response: 1.00  Turnaround 524.33  Wait 321.33
-----
Compare those three:
100.
FIFO:    Average -- Response: 82.00  Turnaround 150.00  Wait 82.00
SJF:   Average -- Response: 54.00  Turnaround 122.00  Wait 54.00
RR:   Average -- Response: 1.00  Turnaround 176.00  Wait 108.00

=> For length = 100, the SJF have the shortest turnaround, and wait time. RR is the longest turn around and wait time.

200. 
FIFO:   Average -- Response: 163.33  Turnaround 298.67  Wait 163.33
SJF:   Average -- Response: 107.33  Turnaround 242.67  Wait 107.33
RR:   Average -- Response: 1.00  Turnaround 350.00  Wait 214.67
=> for length = 200, still the same 

300. 
FIFO:   Average -- Response: 107.33  Turnaround 242.67  Wait 107.33
SJF:    Average -- Response: 160.67  Turnaround 363.67  Wait 160.67
RR:     Average -- Response: 1.00  Turnaround 524.33  Wait 321.33



======================================================================


4. . For what types of workloads does SJF deliver the same turnaround
times as FIFO? around 100-200 

======================================================================

5. For what types of workloads and quantum lengths does SJF deliver
the same response times as RR?
=> Based on the quantum length of the RR, the longer the same response time as RR will more at the same type. 

======================================================================

6. What happens to response time with SJF as job lengths increase?
Can you use the simulator to demonstrate the trend?


======================================================================
7. What happens to response time with RR as quantum lengths increase? Can you write an equation that gives the worst-case response time, given N jobs?









