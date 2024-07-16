#include "parta.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Converts an array of CPU bursts to an array of printect control 
 * blocks to schedule.
 * 
 * @param bursts A list of processes and their bursts times
 * @param blen The number of processes to schedule
 * @return array of printed control blocks.
 */
struct pcb* init_procs(int* bursts, int blen) {
    if (bursts == NULL){
        return 0;
    }
    struct pcb *procs = malloc(sizeof(bursts) * (blen+2));
    int pid_count = 0;
    for(int i = 0; i < blen; i++){
        procs[i].burst_left = bursts[i];
        procs[i].pid = pid_count;
        procs[i].wait = 0;
        pid_count++;
    }
    return procs;
}
/**
 * Determines the next process that would need to be scheduled
 * using the first come first serve scheduling method
 * 
 * @param current The index of the process running
 * @param procs The queue of processes and their properties
 * @param plen The number of processes in queue
 * @return Next process 
 */
int fcfs_next(int current, struct pcb* procs, int plen) {
    if((procs == NULL) || (plen-current == 1)){
        return -1;
    } else if(plen-current >= 0){
        return current+1;
    }
    return -1;
}

/**
 * Calculates the average wait time for processes using 
 * first come first serve scheduling 
 * 
 * @param bursts A list of processes about their time length
 * @param blen The number of processes in bursts
 * @return average wait time of all processes
 */
double fcfs_avg_wait(int* bursts, int blen) {
    if (blen == 1){
        return 0;
    }
    double total_wait = 0.0;
    double wait_before = 0.0;
    for(int i = 0; i < blen-1; i++){
        total_wait += bursts[i] + wait_before;
        wait_before = total_wait;
    }
    return (total_wait/blen);
}

/**
 * Determines the next process that would need to be scheduled
 * using the round robing scheduling method
 * 
 * @param current The index of the process running
 * @param procs The queue of processes and their properties
 * @param plen The number of processes in queue
 * @return Next process 
 */
int rr_next(int current, struct pcb* procs, int plen) {
    if(plen == 1 || procs == NULL){
        return -1;
    } else{
        if(procs[current].pid == plen-1){ // if no more processes
            return 0;
        } else if(procs[current].burst_left <= 4){ // 4 needs to be quantum
            int i = current + 1;
            while(procs[i].burst_left == 0){ // if next process is empty skip
                i++;
            }           
            return i;
        }
    }
    return -1;
}

/**
 * Calculates the average time for a round robin process with a given
 * quantum.
 * 
 * @param bursts A list of processes about their time length
 * @param blen The number of processes in bursts
 * @param quantum The time increments that a process runs for at a time
 * @return average wait time of all processes
 */
double rr_avg_wait(int* bursts, int blen, int quantum) {
    if(blen <= 1 || bursts == NULL){
        return 0.0;
    } else{
        float total_wait = 0;
        int i = 0;
        // Creates a temporary array for wait times of all processes
        // while a process is running
        int *temp = malloc(sizeof(int)*(blen+1));
        for(int k = 0; k < blen; k++){
            temp[k] = 0;
        }
        // loops over processes until all of them are with 0 bursts left
        while(1){
            // checks if sums of all bursts is 0
            int left = 0;
            for(int n = 0; n < blen; n++){
                left += bursts[n];
            }
            if(left == 0){
                break;
            }
            // if we have reached the end of processes go to first one
            if(i == blen){
                i = 0;
            }
            if(bursts[i] > quantum){
                // add wait to variables not currently running
                for(int n = 0; n < blen; n++){
                    // not itself and not processes with 0 bursts
                    if(n != i && bursts[n] != 0){
                        temp[n] += quantum; // add wait to process waiting
                    }
                }
                bursts[i] -= quantum;

            } else {
                // add wait to variables not currently running
                for(int n = 0; n < blen; n++){
                    // not itself and not processes with 0 bursts
                    if(n != i && bursts[n] != 0){
                        temp[n] += bursts[i]; // add wait to process waiting
                    }
                }
                bursts[i] = 0;
            }
            i++; // next process
        }
        // calculates total wait of all processes
        for(int k = 0; k < blen; k++){
            total_wait += temp[k];
        }
        free(temp);
        return total_wait/blen; // returns average
    }
    return 0.0;
}
