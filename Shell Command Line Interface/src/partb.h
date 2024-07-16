#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

void split_args(int argc, char* argv[], char* args1[], char* args2[]);
void run_pipe(const char* command1, char* args1[], const char* command2, char* args2[]);

#ifdef __cplusplus
}
#endif

