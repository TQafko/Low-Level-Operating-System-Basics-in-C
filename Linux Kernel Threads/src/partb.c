#include "partb.h"
#include <stdio.h>
#include <pthread.h>

/**
 * This struct contains values that the main thread passes to each
 * child thread.
 */
struct thread_arg {
    int value;      /// The value to fill each element with
    int* array;     /// Pointer to the entire array
    int start_idx;  /// Starting index for this thread
    int end_idx;    /// End index for this thread
};

/** The length of the array to fill */
enum { ARRAY_LEN = 256 };
/** How many to print per line */
enum { PERLINE = 32 };

/**
 * Prints an array with commas and 32 elements in each line
 * @param array The list with the elements to be printed
 * @param alen Length of elements in array
 * @return none
 */
void print_array(int* array, int alen) {
    int count = 1;
    for(int i = 0; i < alen; i++){
        if(count == PERLINE){
            printf("%d\n", array[i]);
            count = 1;
        } else {
            printf("%d,", array[i]);
            count ++;
        }
    }
}

/**
 * This program uses threads to initialize an array of integers
 */
int main(int argc, char* argv[]) {
    if(argc != 2){
        printf("USAGE:\n  %s NTHREADS\n", argv[0]);
        return 1;
    }

    int nThreads = atoi(argv[1]);
    if(nThreads <= 0){
        printf("ERROR: NTHREADS should be positive integer\n");
        return 1;
    }

    int array[ARRAY_LEN];

    pthread_t *tid = malloc(nThreads*sizeof(pthread_t));
    struct thread_arg *vals = malloc(nThreads*sizeof(struct thread_arg));

    int length = ARRAY_LEN / nThreads;

    for(int i = 0; i < nThreads; i++){
        vals[i].value = i;
        vals[i].array = array;
        vals[i].start_idx = length * i;
        vals[i].end_idx = length * (i + 1);
        pthread_create(&tid[i], NULL, &thrd_main, &vals[i]);
    }

    for(int i = 0; i < nThreads; i++){
        pthread_join(tid[i], NULL);
    }

    print_array(vals->array, ARRAY_LEN);

    free(tid);
    free(vals);
    tid = NULL;
    vals = NULL;
    return 0;
}

/**
 * Sets the array elements of a struct into the values it requests
 * @param args  Contains a struct with value, array, start index,
 *              and end index.
 */
void* thrd_main(void* args) {
    struct thread_arg *vals = (struct thread_arg*)args;
    for(int i = vals->start_idx; i < vals->end_idx; i++){
        vals->array[i] = vals->value;
    }
    return NULL;
}

