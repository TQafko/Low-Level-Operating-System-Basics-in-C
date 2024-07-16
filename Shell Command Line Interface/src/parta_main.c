#include <stdio.h> // For printf/fgets and others
#include <unistd.h> // For certain syscalls
#include <stdlib.h>
#include <sys/wait.h>

/**
 * Takes the CLI commands and uses the parameters to execute them
 * 
 * @param argc Number of arguments
 * @param argv Pointer to all the arguments
 */
int main(int argc, char* argv[]) {
    
    // If not enought arguments given then error
    if (argc < 2){
        printf("USAGE:\n  parta_main CMD CMD_ARGS");
        return 1;
    }
    char *myargs[128]; // 128 is a placeholder
    for(int i = 0; i <= argc; i++){
        myargs[i] = argv[i+1];
    }
    execv(argv[1], myargs);
    return 0;
}
