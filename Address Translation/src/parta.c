#include "parta.h"
#include <stdio.h>

/**
 * The function takes a virtual address and returns the offset
 * of of the address given a set of bits from the call
 * 
 * @param address Address that contains offset bits
 * @param offset_bits The number of bits in the offset
 * @return Offset
 */
int get_offset(int address, int offset_bits) {
    int bitwise = (1 << offset_bits) - 1;
    return (address & bitwise);
}
/**
 * The function returns the page number to be used to find the 
 * frame number
 * 
 * @param address Address that contains pagenumber bits
 * @param offset_bits The number of bits in the offset
 * @return Page Number
 */
int get_pagenum(int address, int offset_bits) {
    return (address >> offset_bits);
}
/**
 * The function combines page number and offset to return a 
 * physical address in memory
 * 
 * @param fn The frame number of the address
 * @param offset The offset of the address
 * @param offset_bits The number of bits in the offset
 * @return Physical address
 */
int get_physaddr(int fn, int offset, int offset_bits) {
    int temp = fn << offset_bits;
    return (temp | offset);
}

/**
 * Initilizes a page table with a given number of pages and
 * also the parameter for number of offset bits.
 * 
 * @param num_pages The number of pages that table can have
 * @param offset_bits The number of offset_bits the table works with
 * @return page table
 */
struct pagetable *pg_init(int num_pages, int offset_bits) {
    struct pagetable *page = malloc(sizeof(int)*(num_pages));
    page->num_pages = num_pages;
    page->offset_bits = offset_bits; 
    page->entries = malloc(sizeof(int)*(num_pages));
    return page;
}
/**
 * Terminates a given page table due to its use of dynamic memory
 * 
 * @param table The page table to be terminated
 */
void pg_term(struct pagetable* table) {
    free(table->entries);
    free(table);
}
/**
 * Assigns a frame number to a page number in the given page table
 * 
 * @param table The page table
 * @param pn The page number 
 * @param fn The frame number
 */
void pg_assign(struct pagetable* table, int pn, int fn) {
    table->entries[pn] = fn;
}
/**
 * Given a virtual address, a physical address to the memory is 
 * returned
 * 
 * @param table The page table to be used 
 * @param address The virtual address
 * @return The physical address in memory
 */
int pg_lookup(struct pagetable* table, int address) {
    int offset = get_offset(address, table->offset_bits);
    int page_num = get_pagenum(address, table->offset_bits);
    if(page_num >= table->num_pages){
        return -1;
    }
    int fn = table->entries[page_num];
    int physical_addr = get_physaddr(fn, offset, table->offset_bits);
    return physical_addr;
}
