#include <gtest/gtest.h>
#include "parta.h"

TEST(PartA, get_offset) { 
    // Tests for address 0x15
    ASSERT_EQ(0b1, get_offset(0x15, 1));
    ASSERT_EQ(0b1, get_offset(0x15, 2));
    ASSERT_EQ(0b101, get_offset(0x15, 3));
    ASSERT_EQ(0b101, get_offset(0x15, 4));
    ASSERT_EQ(0x15, get_offset(0x15, 5));
    ASSERT_EQ(0x15, get_offset(0x15, 6));

    // Tests for address 0x37
    ASSERT_EQ(0b1, get_offset(0x37, 1));
    ASSERT_EQ(0b11, get_offset(0x37, 2));
    ASSERT_EQ(0b111, get_offset(0x37, 3));
    ASSERT_EQ(0b111, get_offset(0x37, 4));
    ASSERT_EQ(0x17, get_offset(0x37, 5));
    ASSERT_EQ(0x37, get_offset(0x37, 6));

    // Tests for address 0x2C
    ASSERT_EQ(0, get_offset(0x2C, 1));
    ASSERT_EQ(0, get_offset(0x2C, 2));
    ASSERT_EQ(0x4, get_offset(0x2C, 3));
    ASSERT_EQ(0xC, get_offset(0x2C, 4));
    ASSERT_EQ(0xC, get_offset(0x2C, 5));
    ASSERT_EQ(0x2C, get_offset(0x2C, 6));
}

TEST(PartA, get_pagenum) { 
    // Tests for address 0x15
    ASSERT_EQ(0b1010, get_pagenum(0x15, 1));
    ASSERT_EQ(0b101, get_pagenum(0x15, 2));
    ASSERT_EQ(0b10, get_pagenum(0x15, 3));
    ASSERT_EQ(0b1, get_pagenum(0x15, 4));
    ASSERT_EQ(0, get_pagenum(0x15, 5));
    ASSERT_EQ(0, get_pagenum(0x15, 6));

    // Tests for address 0x37
    ASSERT_EQ(0b11011, get_pagenum(0x37, 1));
    ASSERT_EQ(0b1101, get_pagenum(0x37, 2));
    ASSERT_EQ(0b110, get_pagenum(0x37, 3));
    ASSERT_EQ(0b11, get_pagenum(0x37, 4));
    ASSERT_EQ(0b1, get_pagenum(0x37, 5));
    ASSERT_EQ(0, get_pagenum(0x37, 6));

    // Tests for address 0x2C
    ASSERT_EQ(0b0010110, get_pagenum(0x2C, 1));
    ASSERT_EQ(0b001011, get_pagenum(0x2C, 2));
    ASSERT_EQ(0b00101, get_pagenum(0x2C, 3));
    ASSERT_EQ(0b0010, get_pagenum(0x2C, 4));
    ASSERT_EQ(0b001, get_pagenum(0x2C, 5));
    ASSERT_EQ(0, get_pagenum(0x2C, 6));
}
TEST(PartA, get_physaddr) { 
    ASSERT_EQ(0b111, get_physaddr(1, 0b11, 2));
    ASSERT_EQ(0b1011, get_physaddr(1, 0b11, 3));
    ASSERT_EQ(0b10011, get_physaddr(1, 0b11, 4));
    ASSERT_EQ(0b100011, get_physaddr(1, 0b11, 5));

    ASSERT_EQ(0b110, get_physaddr(1, 0b10, 2));
    ASSERT_EQ(0b1010, get_physaddr(1, 0b10, 3));
    ASSERT_EQ(0b10010, get_physaddr(1, 0b10, 4));
    ASSERT_EQ(0b100010, get_physaddr(1, 0b10, 5));
}

 
TEST(PartA, pg_init_term) { 
    struct pagetable* table = NULL;

    table = pg_init(8, 1);
    ASSERT_NE(nullptr, table);
    pg_term(table);

    table = pg_init(8, 3);
    ASSERT_NE(nullptr, table);
    pg_term(table);

    table = pg_init(8, 4);
    ASSERT_NE(nullptr, table);
    pg_term(table);
}

TEST(PartA, pg_assign) { 
    struct pagetable* table = NULL;
    table = pg_init(8, 4);
    ASSERT_NE(nullptr, table);

    pg_assign(table, 0, 0x17);
    pg_assign(table, 1, 0x16);
    pg_assign(table, 2, 0x15);
    pg_assign(table, 3, 0x14);
    pg_assign(table, 4, 0x13);
    pg_assign(table, 5, 0x12);
    pg_assign(table, 6, 0x11);
    pg_assign(table, 7, 0x10);

    pg_term(table);
}
TEST(PartA, pg_assign_lookup) { 
    // Try lookup with page table (8, 4)
    {
        struct pagetable* table = NULL;
        table = pg_init(8, 4);
        ASSERT_NE(nullptr, table);

        pg_assign(table, 0, 0x17);
        pg_assign(table, 1, 0x16);
        pg_assign(table, 2, 0x15);
        pg_assign(table, 3, 0x14);
        pg_assign(table, 4, 0x13);
        pg_assign(table, 5, 0x12);
        pg_assign(table, 6, 0x11);
        pg_assign(table, 7, 0x10);

        // VA 0x8 has page# 0. Table says frame# 0x17, so answer is 0x178
        EXPECT_EQ(0x178, pg_lookup(table, 0x8));

        // VA 0x18 has page# 1. Table says frame# 0x16, so answer is 0x168
        EXPECT_EQ(0x168, pg_lookup(table, 0x18));

        // VA 0x24 has page# 2. Table says frame# 0x15, so answer is 0x154
        EXPECT_EQ(0x154, pg_lookup(table, 0x24));

        // VA 0x72 has page# 7. Table says frame# 0x10, so answer is 0x102
        EXPECT_EQ(0x102, pg_lookup(table, 0x72));

        pg_term(table);
    }
    // Try lookup with page table (8, 3)
    {
        struct pagetable* table = NULL;
        table = pg_init(8, 3);
        ASSERT_NE(nullptr, table);

        pg_assign(table, 0, 0x17);
        pg_assign(table, 1, 0x16);
        pg_assign(table, 2, 0x15);
        pg_assign(table, 3, 0x14);
        pg_assign(table, 4, 0x13);
        pg_assign(table, 5, 0x12);
        pg_assign(table, 6, 0x11);
        pg_assign(table, 7, 0x10);

        // VA 0x8 has page# 1. Table says frame# 0x16 (0b10110), so answer is 0b1011 0000)
        EXPECT_EQ(0b1011'0000, pg_lookup(table, 0x8));

        pg_term(table);
    }
}
