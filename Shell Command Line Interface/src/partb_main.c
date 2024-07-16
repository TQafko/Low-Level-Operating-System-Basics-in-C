#include <stdio.h> // For printf/fgets and others
#include <string.h>
#include <stdlib.h>
#include <unistd.h> // For certain syscalls
#include <sys/wait.h> // For wait
#include "partb.h"
#include <string.h>

int main(int argc, char* argv[]) {
    
    if(argc < 2){
        printf("USAGE:\n  %s CMD1 CMD1_ARGS [: CMD2 CMD2_ARGS]\n", argv[0]);
        return 1;
    }

    bool mode1 = true;
    int args1_len = 1;
    int args2_len = 1; 
    char* command1 = argv[1];
    char* command2 = {""};
    // Commands of functions found here and length of arguments
    // for each command if colon exists
    for(int i = 0; i < argc; i++){
        if(strcmp(argv[i], ":") == 0){
            mode1 = false;
            command2 = argv[i+1];
        } 
        if(mode1){
            args1_len +=1;
        } else {
            args2_len +=1;
        }
    }
    if(mode1){
        char *myargs[128];  // 128 is a placeholder
        for(int i = 0; i < argc; i++){
            myargs[i] = argv[i+1];
        }
        execv(argv[1], myargs);
    } else if(!mode1) {
        char** args1 = malloc(sizeof(char*) * args1_len);
        char** args2 = malloc(sizeof(char*) * args2_len);
        split_args(argc, argv, args1, args2);
        run_pipe(command1, args1, command2, args2);
        free(args1);
        free(args2);
        args1 = NULL;
        args2 = NULL;
    }
    return 0;
}
