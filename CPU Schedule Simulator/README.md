# README

## Introduction

A simple CPU schedule simulator.

### parta.c

#### Init

    struct pcb* init_procs(int* bursts, int blen);

The first function completes `init_procs`. This function takes an array of CPU bursts,
and returns an array of PCBs. The PCBs are created in the heap, and each object contains the
PID, burst_left, and the total wait this process has experienced so far.

#### Scheduling

    double fcfs_avg_wait(int* bursts, int blen);
    double rr_avg_wait(int* bursts, int blen, int quantum);
 
Given an array of CPU bursts (and the time quantum for round-robin). Creates the array of
PCBs using `init_procs`, and then starts scheduling. Keeps track of each process' wait time by
looking at the PCB array's `wait` variable.

First-come-first-serve scheduling will start from index 0 and run each process until completion.

Round-robin scheduling will take an additional parameter (`quantum`). Each process will run until it
runs out of CPU burst or the time quantum (whichever comes first). 

Assume that all processes arrived that the same time, but in the order listed in `bursts`.

#### Next Process

    int fcfs_next(int current, struct pcb* procs, int plen);
    int rr_next(int current, struct pcb* procs, int plen);

A helper function called `next` is provided to make it easier to develop the scheduler. These
functions return the next process to run. For example, let's say there are 2 processes total. If the current process is P0, under FCFS the
next process would be P1. If the current process is P1, this would be the end, so return -1.

Under round robin, if the current process is P0, next is p1; if current is P1, next is P0. If all
the processes are complete (burst_left is 0), then return -1.

### parta_main.c

Command-line arguments are processed such as the first argument is the algorithm to use: "fcfs" or
"rr". If using fcfs, then remaining values are the array of CPU bursts. If using rr, the immediate
next value is the time quantum, and the CPU bursts follow that.

After identifying the algorithm to use, prints the current setting and then print the average wait
time (up to 2 decimal points). For example, if we want fcfs with 3 processes:

    $ ./build/src/parta_main fcfs 4 5 9
    Using FCFS.
    Accepted P0: Burst 4
    Accepted P1: Burst 5
    Accepted P2: Burst 9

    Average wait time: 3.33

If we want round-robin with time quantum 2, with 3 processes:

    $ ./build/src/parta_main rr 2 4 5 9
    Using RR(2).
    Accepted P0: Burst 4
    Accepted P1: Burst 5
    Accepted P2: Burst 9

If the command-line arguments are not correctly provided, print a usage message and exit with status
1 immediately. For example:

    $ ./build/src/parta_main rr 2
    Usage:
      parta_main fcfs|rr BURSTS

    $ ./build/src/parta_main first-come-first-serve 10
    Usage:
      parta_main fcfs|rr BURSTS

You may use any function from stdlib.h, stdio.h, string.h, or ctype.h. For example, `strcmp` or `atoi`
can be used.

To test this part, run the following command in the terminal:

    ./run.sh testa
