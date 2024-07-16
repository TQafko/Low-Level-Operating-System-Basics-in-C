#include "parta.h"
#include <stdlib.h> // For malloc/free

bool find_cycle(int *wait_for, int num_procs) {
    bool cycle = 0;
    bool *marked = malloc(num_procs*sizeof(bool));
    for (int i = 0; i < num_procs; i++) {
        marked[i] = 0;
    }
    for(int v = 0; v < num_procs; v++){
        if(!marked[v]){
            marked[v] = 1;

            bool *inPath = malloc((num_procs)*(sizeof(bool)));
            for (int i = 0; i < num_procs; i++) {
                inPath[i] = 0;
            }
            inPath[v] = 1;

            cycle = find_cycle_from(wait_for, num_procs, v, marked, inPath);

            free(inPath);
            if(cycle){
                free(marked);
                return cycle;
            }
        }
    }
    free(marked);

    return cycle;
}
bool find_cycle_from(int *wait_for, int num_procs, int v, bool* marked, bool* in_path) {
    bool cycle = false;

    int X = wait_for[v];
    if(X == -1){
        cycle = false;
    } else if(in_path[X]){
        cycle = true;
    } else if(marked[X] == false){
        marked[X] = true;
        in_path[X] = true;
        cycle = find_cycle_from(wait_for, num_procs, X, marked, in_path);
    }
    return cycle;
}

