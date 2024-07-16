#include <stdio.h> // For printf/fgets and others
#include <unistd.h> // For certain syscalls
#include <string.h>
#include "partb.h"
#include <string.h>

/**
 * Splits a system call arguments into two if a colon exists 
 * in the call, indicating two system calls
 * 
 * @param argc number of arguments in system call
 * @param argv the arguments of system call
 * @param args1 the arguments for the command before colon
 * @param args2 the arguments for the command after colon
 */
void split_args(int argc, char* argv[], char* args1[], char* args2[]) {
    bool command2 = false; // Indicates if colon exists
    int index_arg2 = 0; // Index for adding elements to args2
    int i = 1;
    while(argv[i] != NULL){
        if(strcmp(argv[i], ":") == 0){
            args1[i-1] = NULL;
            i++;
            command2 = true;
            break;
        }
        args1[i-1] = argv[i];
        i++;
    }
    if(command2) {
        while(argv[i] != NULL){
            args2[index_arg2] = argv[i];
            index_arg2++;
            i++;
        } 
        args2[index_arg2] = NULL;
    }
}

/**
 * Takes two commands with their arguments 
 * and runs them using child and parent processes
 * 
 * @param command1 the first name of the first command to run 
 * @param command2 the second name of the second command to run
 * @param args1 the arguments for command 1
 * @param args2 the arguments for command 2
 */
void run_pipe(const char* command1, char* args1[], const char* command2, char* args2[]) {
     // Create pipe
        int fd[2];
        int pret = pipe(fd);
        if(pret == -1) {
            perror("pipe failed");
            
        }
        int read_fd = fd[0];
        int write_fd = fd[1];

        //create child process
        int fret = fork();
        if(fret > 0) {
            // Parent writes
            close(read_fd);
            dup2(write_fd, STDOUT_FILENO);
            execv(command1, args1);
        } else if (fret == 0) {
            // Child reads
            close(write_fd);
            dup2(read_fd, STDIN_FILENO);
            execv(command2, args2);
        } else {
            // Error
            perror("fork failed");
        }
}

