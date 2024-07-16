# README

## Introduction

This is an example of an address translation scheme using simple paging.

### Part A

The basics of a page table simulator. After initializing the page
table, code is supposed to translate any given address into its physical address.

#### Part A.1

Helper functions. Given an address, splits the address into the offset
and page number. Reconstructs the physical address from two pieces, the frame number and page number.

    int get_offset(int address, int offset_bits);
    int get_pagenum(int address, int offset_bits);
    int get_physaddr(int fn, int offset, int offset_bits);

Bitwise operators are used.

- `<<` means left shift by N bits. For example `1<<2` is `0b100`
- `>>` means right shift by N bits. For example `0b1000>>2` is `0b10`
- `|` means bitwise OR. You can use this to combine bits. For example, `0b1100 | 0b1010` is `0b1110`
- `&` means bitwise AND. Extract bits by using a bitmask. For example `0b1101 &
  0b11` will give you the bottom 2 bits: `0b01`

The first function is used to get the page offset. Can generate a bitmask of 3 bits by shifting
left 1 by 3 and subtracting 1. Shift left by 3 gives you `0b1000`, and subtracting by 1 give you
`0b111`. Using a bitwise AND with this gives you the bottom 3 bits.

The second function is used to get the page number. Use a right shift operator to discard the offset
bits.

The last function is used to combine frame number and offset.

#### Part A.2

Once the helper functions are set up, can now create the page table. Note that all addresses are
assumed to contain 12 bits.

    struct pagetable {
        int num_pages;
        int offset_bits;
        int* entries;
    };

The page table contains the above entries. Most importantly, the `entries` part is an array of page
number to frame number mappings. For example:

    {3, 7, 1, 0}

means page 0 is mapped to frame 3, page 1 to frame 7, page 2 to frame 1, and page 3 to frame 0. This
can be variable length, so it's a malloc'd array.

    struct pagetable *pg_init(int num_pages, int offset_bits);
    void pg_term(struct pagetable* table);

#### Part A.3

The last part uses the page table. The first function simply updates an entry. The second function
has you look up an entry and return the physical address. If the address is invalid (i.e. exceeds
the 12 bits), return -1.

    void pg_assign(struct pagetable* table, int pn, int fn);
    int pg_lookup(struct pagetable* table, int address);
