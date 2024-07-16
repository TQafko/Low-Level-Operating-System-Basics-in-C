#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

const char* get_hello(void);
bool find_cycle_from(int* wait_for, int num_procs, int v, bool* marked, bool* in_path);
bool find_cycle(int* wait_for, int num_procs);

#ifdef __cplusplus
}
#endif
