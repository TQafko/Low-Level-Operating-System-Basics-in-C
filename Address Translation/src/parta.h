#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h> // For true/false
#include <stdlib.h> // For malloc/free

int get_offset(int address, int offset_bits);
int get_pagenum(int address, int offset_bits);
int get_physaddr(int fn, int offset, int offset_bits);

struct pagetable {
    int num_pages;
    int offset_bits;
    int* entries;
};

struct pagetable *pg_init(int num_pages, int offset_bits);
void pg_term(struct pagetable* table);
void pg_assign(struct pagetable* table, int pn, int fn);
int pg_lookup(struct pagetable* table, int address);

#ifdef __cplusplus
}
#endif
