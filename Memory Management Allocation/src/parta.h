#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h> // For NULL
#include <stdbool.h> // For true/false

enum { OWNER_NOBODY = -1 };

struct mem_region {
    int size;
    int owner;
    struct mem_region* next;
};

struct regions {
    struct mem_region* list;
    int left;
};

struct mem_region* mem_region_init(int size);
void mem_region_term(struct mem_region* regions);

void mem_region_assign(struct mem_region* r, int requester, int size);
void mem_region_merge_empty(struct mem_region* regions);

void mem_region_alloc(struct mem_region* regions, int requester, int size);
void mem_region_free(struct mem_region* regions, int owner);

#ifdef __cplusplus
}
#endif
