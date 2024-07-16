/*******************************************************************
 * Tedi Qafko
 * Assignment 9
 * April 6th
 *******************************************************************
 * Material by Leonidas Deligiannidis (deligiannidisl@wit.edu)
 * is licensed under a Creative Commons Attribution-NonCommercial
 * 3.0 Unported License
 * (http://creativecommons.org/licenses/by-nc/3.0/).
 *******************************************************************/
/**********************************************
 *                                            *
 *   IPC One parent process NPROC children    *
 *                                            *
 **********************************************/

#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "partb.h"
// VSCode doesn't like signal.h for some reason
int kill(pid_t pid, int sig);

/**********************************************
 *                                            *
 * Configuration settings                     *
 *                                            *
 **********************************************/
#define NPROC (2)     /** number of children processes */
#define MAXLOCKS (10) /** Total available resources (size of the lock table) */
#define MAXCHILDLOCKS                                                                            \
    (4) /** max resource a child can hold before requesting 'release locks' from the LockManager \
         */

/**
 * Code for the child processes
 */
void child(int child_id, int req, int ack) {
    int count = 0; /* It is used for num of locks and check if we exceed MAXCHILDLOCKS */

    srand(child_id + 1);

    /* Loop until forever, */
    for (;;) {
        struct msg_requestLock MSG;    /* message from child (me) to parent */
        struct msg_requestStatus STAT; /* message from parent to child (me) */

        MSG.lockID = rand() % MAXLOCKS;
        MSG.Action = LOCK;

        printf("\tChild %d: Requesting lock %d . . .\n", child_id, MSG.lockID);
        fflush(stdout);

        /*
         * Both calls are blocked if there is nothing to do.
         */

        write(req, (char *)&MSG, sizeof(MSG));
        read(ack, (char *)&STAT, sizeof(STAT));

        if (STAT.status == GRANTED) { /* Success got lock */
            count++;
            printf("\tChild %d: Got lock %d (%d).\n", child_id, MSG.lockID, count);
            fflush(stdout);
        } else if (STAT.status == NOT_GRANTED) {
            printf("Child %d waiting for lock %d\n", child_id, MSG.lockID);
            fflush(stdout);

            /*
             * I will get it shortly or the LockManager
             * will NOT give it to me to prevent a deadlock.
             */
            read(ack, (char *)&STAT, sizeof(STAT));
            if (STAT.status == GRANTED) {
                count++;
                printf("\tChild %d: Got lock %d (%d).\n", child_id, MSG.lockID, count);
            } else if (STAT.status == PREVENT) {
                printf("CHILD: %d Will try again, (preventing)\n", child_id);
                fflush(stdout);
            } else {
                printf("CHILD: %d    FATAL ERROR\n", child_id);
                fflush(stdout);
                kill(getppid(), SIGTERM);
            }
        }

        if (count >= MAXCHILDLOCKS) {
            /*
             * Child submits request to release all its locks
             */
            printf("\tChild %d: Submitting RELEASE_ALL.\n", child_id);
            fflush(stdout);

            MSG.Action = RELEASE_ALL;
            write(req, (char *)&MSG, sizeof(struct msg_requestLock));

            count = 0;
        }

        sleep(1);
    } /* for(;;) */
} /* child */

/**
 * Print the lock table so that YOU see what your program is doing
 */
void PrintLocks(struct Lock locks[]) {
    printf("[ ");
    for(int i = 0; i < MAXLOCKS; i++){
        if(locks[i].is_owned == 1){
            if(i == MAXLOCKS-1){
                printf("L%d", locks[i].by_child);
            } else {
                printf("L%d, ", locks[i].by_child);
            }
        } else if(locks[i].is_owned == 0){
            if(i == MAXLOCKS-1){
                printf("NA");
            } else {
                printf("NA, ");
            }
            
        }
    }
    printf(" ]\n");
}

/**
 * Print the waiting table so that YOU see what your program is doing
 */
void PrintWaitingList(int waiting[]) {
    printf("[ ");
    for(int i = 0; i < NPROC; i++){
        if(waiting[i] == 1){
            if(i == NPROC-1){
                printf("Waiting");
            } else {
                printf("Waiting, ");
            }
        } else if(waiting[i] == -1){
            if(i == NPROC-1){
                printf("NA");
            } else {
                printf("NA, ");
            }
        }
    }
    printf(" ]; ");
}

/**
 * Checks for the case where a deadlock occurs and two processes are 
 * waiting due to a loop occuring.
 */
bool CheckForDeadLock(int waiting[]) {
    int count = 0;
    for (int i = 0; i < NPROC; i++){
        if(waiting[i] == 1){
            count ++;
        }
    }
    if(count >= NPROC){
        return true;
    }
    return false;
}

/**
 * Unlcoks all locks when the program has reached its max number of locks 
 */
void handleReleaseAll(struct Lock locks[], int waiting[], int cid, int respond[]) {
    for (int li = 0; li < MAXLOCKS; li++) {
        locks[li].is_owned = false;
    }
    // PrintLocks(locks);
}

/**
 * It returns the approriate status message to the child weather
 * the request was accepted or not granted.
 */
void handleRequest(struct Lock locks[], int waiting[], int cid, int t_lock, int respond_fd) {
    struct msg_requestStatus STAT; /* message from parent to child (me) */
    for (int li = 0; li < MAXLOCKS; li++) {
        if(li == t_lock){
            // Check which lock the requests looks for
            if(locks[li].is_owned == 1){
                // if the process is occupied
                if(locks[li].by_child == t_lock){
                    STAT.status = YOU_OWN_IT;
                } else {
                    // someone else owns the lock
                    STAT.status = NOT_GRANTED;
                    waiting[cid] = 1;
                    if(CheckForDeadLock(waiting)){
                        // deadlock detected
                        // two processes waiting
                        for (int i = 0; i < NPROC; i++){
                            waiting[i] = -1;
                        }
                        STAT.status = PREVENT;
                    } else if(waiting[cid] == cid){
                        // deadlock detected
                        // Two processes access the same lock
                        for (int i = 0; i < NPROC; i++){
                            waiting[i] = -1;
                        }
                        STAT.status = PREVENT;
                    }
                }
            } else if(locks[li].is_owned == 0){
                // lock the process
                locks[li].is_owned = true;
                STAT.status = GRANTED;
            }
        }
        
    }
    // Print to screen
    PrintWaitingList(waiting);
    PrintLocks(locks);
    write(respond_fd, (char *)&STAT, sizeof(struct msg_requestStatus));
}

void parent(int listen[], int respond[]) {

    /**
     * Array of locks owned by the manager. The manager will parcel out locks
     * to child processes when they request them (if the request is valid).
     */
    struct Lock locks[MAXLOCKS];
    for (int li = 0; li < MAXLOCKS; li++) {
        locks[li].is_owned = false;
    }

     /** Lock index if the process is waiting for some lock, or -1 if not */
    int waiting[NPROC];
    for (int cid = 0; cid < NPROC; cid++) {
        waiting[cid] = -1;
    }

    /* Loop until forever, */
    for (;;) {
        for (int cid = 0; cid < NPROC; cid++) {
            struct msg_requestLock ChildRequest;
            int nb = read(listen[cid], (char *)&ChildRequest, sizeof(ChildRequest));

            if (nb == sizeof(ChildRequest)) {
                if (ChildRequest.Action == RELEASE_ALL) {
                    handleReleaseAll(locks, waiting, cid, respond);
                } else if (ChildRequest.Action == LOCK) {
                    handleRequest(locks, waiting, cid, ChildRequest.lockID, respond[cid]);
                }
            }
        }
    }
}

/** Child proceess PIDs. Used in abortAll() */
pid_t pids[NPROC];

/**
 * Terminate all child processes. Called at the end to cleanup.
 */
void abortAll() {
    printf("TERMINATING...\n");

    for (int cid = 0; cid < NPROC; cid++) {
        kill(pids[cid], SIGKILL);
    }
    exit(0);
}

/******************************************************************
 *
 ******************************************************************/
int main(int argc, char **argv) {
    int listen[NPROC];
    int respond[NPROC];

    /*
     * Arrange for termination to call the cleanup procedure
     */
    signal(SIGTERM, abortAll);

    /*
     * Initialize pipes and fork the children processes
     */
    for (int cid = 0; cid < NPROC; cid++) {
        int parent_to_child[2];
        int child_to_parent[2];

        /*
         * Create the child -> parent pipe.
         */
        pipe(child_to_parent);
        listen[cid] = child_to_parent[0];
        fcntl(listen[cid], F_SETFL, O_NONBLOCK);

        /*
         * Create the parent -> child pipe.
         */
        pipe(parent_to_child);
        respond[cid] = parent_to_child[1];
        fcntl(respond[cid], F_SETFL, O_NONBLOCK);

        /*
         * Create child process.
         */

        if ((pids[cid] = fork()) == 0) {
            /*
             * *********** Child process code. ***********
             */
            signal(SIGTERM, SIG_DFL);
            close(parent_to_child[1]);
            close(child_to_parent[0]);

            child(cid, child_to_parent[1], parent_to_child[0]);

            return 0;
        }

        close(child_to_parent[1]);
        close(parent_to_child[0]);
    }

    parent(listen, respond);

    return 0;
}
