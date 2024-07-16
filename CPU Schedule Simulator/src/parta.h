#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

/** This struct contains various information about each process */
struct pcb {
    int pid;        /** The process ID */
    int burst_left; /** The amount of burst left */
    int wait;       /** The amount of time this process was stuck waiting */
};


struct pcb* init_procs(int* bursts, int blen);

int fcfs_next(int current, struct pcb* procs, int plen);
double fcfs_avg_wait(int* bursts, int blen);

int rr_next(int current, struct pcb* procs, int plen);
double rr_avg_wait(int* bursts, int blen, int quantum);

#ifdef __cplusplus
}
#endif

