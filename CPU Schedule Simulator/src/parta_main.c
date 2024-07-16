#include "parta.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if(argc < 3){
        printf("Usage:\n  parta_main fcfs|rr BURSTS");
        return 1;
    }     
    int *bursts = malloc(sizeof(int)*argc);
    int count = 0;
    double wait = 0;
    if(strcmp(argv[1], "fcfs") == 0){
        // For first come first server scheduling command
        printf("Using FCFS\n\n");
        for(int i = 0; i < argc-2; i++){
            printf("Accepted P%d: Burst %s\n", i, argv[i+2]);
        }
        for(int i = 0; i < argc-2; i++){
            bursts[i] = atoi(argv[i+2]);
            count ++;
        }
        wait = fcfs_avg_wait(bursts, count);
        printf("Average wait time: %.2f\n", wait);
    } else if(strcmp(argv[1], "rr") == 0){
        // For round robin scheduling using quantum of first element
        printf("Using RR(%s).\n\n", argv[2]);
        for(int i = 0; i < argc-3; i++){
            printf("Accepted P%d: Burst %s\n", i, argv[i+3]);
        }
        for(int i = 0; i < argc-3; i++){
            bursts[i] = atoi(argv[i+3]);
            count ++;
        }
        wait = rr_avg_wait(bursts, count, atoi(argv[2]));
        printf("Average wait time: %.2f\n", wait);
    }
    free(bursts);
    return 0;
}
