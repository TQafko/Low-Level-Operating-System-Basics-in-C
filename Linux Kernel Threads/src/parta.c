#include "parta.h"
#include <stdio.h>
#include <pthread.h>
#include <ctype.h> 

/**
 * This program creates threads and has each thread prints its own number and exits
 */
int main(int argc, char* argv[]) {
    if (argc != 2){
        printf("USAGE:\n  %s NTHREADS\n", argv[0]);
        return 1;
    }

    int nThreads = atoi(argv[1]);
    if(nThreads <= 0){
        printf("ERROR: NTHREADS should be positive integer\n");
        return 1;
    }

    // Create array of ints and initialize them
    int* data = malloc(sizeof(int) * nThreads);
    for (int i = 0; i < nThreads; i++) {
        data[i] = i;
    }

    // Initilizes threads in a heap variable
    pthread_t *tids = malloc((nThreads)*sizeof(pthread_t));

    // Calls the threads with parameter 0 to n
    for (int i = 0; i < nThreads; i++) {
        pthread_create(&tids[i], NULL, thrd_main, &data[i]);
    }

    // Waits for all the threads to be done 
    for(int i = 0; i < nThreads; i++){
        pthread_join(tids[i],NULL);
    }

    printf("Main cleans up\n");

    free(tids);
    free(data);
    tids = NULL;
    data = NULL;

    return 0;
}

void* thrd_main(void* args) {
    int* num = (int*)args;
    printf("Hello, I'm thread %d\n", *num);
    return NULL;
}

