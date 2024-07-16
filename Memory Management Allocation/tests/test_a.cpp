#include <gtest/gtest.h>
#include "parta.h"

/**
 * Return the length of the regions linked list
 *
 * @param regions The linked list of regions
 * @returns The length, or 0 if regions is NULL
 */
int region_length(struct mem_region* regions) {
    struct mem_region* r = regions;
    int i = 0;
    while(r != NULL) {
        r = r->next;
        i++;
    }
    return i;
}
/**
 * Return a pointer to a specified region in the regions linked list
 *
 * @param regions The linked list of regions
 * @param idx The index of the region to look at
 * @returns The pointer, or NULL if `idx` is invalid
 */
struct mem_region* region_at(struct mem_region* regions, int idx) {
    if(idx < 0) {
        return NULL;
    } else if(idx == 0) {
        return regions;
    } else {
        struct mem_region* r = regions;
        int i = 0;
        while(r != NULL && i < idx) {
            r = r->next;
            i++;
        }
        if(i == idx) {
            return r;
        } else {
            return NULL;
        }
    }
}


/**
 * A special macro function that checks if the specified region is owned by `owner`.
 * If the linked list doesn't have enough entries, calls FAIL.
 *
 * @param regions The linked list of regions
 * @param idx The index of the region to look at
 * @param owner The owner ID
 * @param size The size
 */
#define EXPECT_REGION_EQ(_regions, _idx, _owner, _size) do {        \
    struct mem_region* r = region_at(_regions, _idx);               \
    if(r != NULL) {                                                 \
        EXPECT_EQ(_owner, r->owner);                                \
        EXPECT_EQ(_size, r->size);                                  \
    } else {                                                        \
        FAIL() << "regions(" << (_idx) << ") doesn't exist";        \
    }                                                               \
} while(0)


TEST(PartA, init) { 
    ASSERT_EQ(nullptr, mem_region_init(0));
    ASSERT_EQ(nullptr, mem_region_init(-1));

    // Test for init(10)
    {
        struct mem_region* regions = mem_region_init(10);

        ASSERT_NE(nullptr, regions);

        EXPECT_EQ(1, region_length(regions));
        EXPECT_REGION_EQ(regions, 0, OWNER_NOBODY, 10);

        free(regions);
    }

    // Test for init(100)
    {
        struct mem_region* regions = mem_region_init(100);
        
        ASSERT_NE(nullptr, regions);

        EXPECT_EQ(1, region_length(regions));
        EXPECT_REGION_EQ(regions, 0, OWNER_NOBODY, 100);

        free(regions);
    }
}

TEST(PartA, assign) { 
    // Test for assign(8) into 100
    {
        struct mem_region* regions = mem_region_init(100);
        ASSERT_NE(nullptr, regions);

        mem_region_assign(regions, 0xA, 8);
        
        // Check the results
        EXPECT_EQ(2, region_length(regions));
        EXPECT_REGION_EQ(regions, 0, 0xA, 8);
        EXPECT_REGION_EQ(regions, 1, OWNER_NOBODY, 92);

        mem_region_term(regions);
    }

    // Test for assign(20) into 100
    {
        struct mem_region* regions = mem_region_init(100);
        ASSERT_NE(nullptr, regions);

        mem_region_assign(regions, 0xA, 20);
        EXPECT_EQ(2, region_length(regions));
        EXPECT_REGION_EQ(regions, 0, 0xA, 20);
        EXPECT_REGION_EQ(regions, 1, OWNER_NOBODY, 80);

        mem_region_term(regions);
    }
}

TEST(PartA, assignInvalid) { 
    // Should not crash
    mem_region_assign(NULL, 0xA, 10);

    // Test for assign(120) into 100. Should be too large
    {
        struct mem_region* regions = mem_region_init(100);
        ASSERT_NE(nullptr, regions);

        // Too big, so no changes
        mem_region_assign(regions, 0xA, 120);

        EXPECT_EQ(1, region_length(regions));
        EXPECT_REGION_EQ(regions, 0, OWNER_NOBODY, 100);

        mem_region_term(regions);
    }

    // Test for assign(-1) into 100
    {
        struct mem_region* regions = mem_region_init(100);
        ASSERT_NE(nullptr, regions);

        // Invalid size, so fail :(
        mem_region_assign(regions, 0xA, -1);

        EXPECT_EQ(1, region_length(regions));
        EXPECT_REGION_EQ(regions, 0, OWNER_NOBODY, 100);
        mem_region_term(regions);
    }


}
TEST(PartA, mergeAllEmpty) { 

    // Test for "merging" a 10 with no one else
    {
        struct mem_region* regions = mem_region_init(10);
        ASSERT_NE(nullptr, regions);

        mem_region_merge_empty(regions);

        // Should have free region of size 10
        EXPECT_EQ(1, region_length(regions));
        EXPECT_REGION_EQ(regions, 0, OWNER_NOBODY, 10);
        mem_region_term(regions);
    }

    // Test for merging a 10 with a 20
    {
        struct mem_region* r1 = mem_region_init(10);
        struct mem_region* r2 = mem_region_init(20);
        ASSERT_NE(nullptr, r1);
        ASSERT_NE(nullptr, r2);

        // Create the linked list
        struct mem_region* regions = r1;
        r1->next = r2;

        mem_region_merge_empty(regions);

        // Should have free region of size 30
        EXPECT_EQ(1, region_length(regions));
        EXPECT_REGION_EQ(regions, 0, OWNER_NOBODY, 30);

        mem_region_term(regions);
    }

    // Test for merging a 10, 20, and a 35
    {
        struct mem_region* r1 = mem_region_init(10);
        struct mem_region* r2 = mem_region_init(20);
        struct mem_region* r3 = mem_region_init(35);
        ASSERT_NE(nullptr, r1);
        ASSERT_NE(nullptr, r2);
        ASSERT_NE(nullptr, r3);

        // Create the linked list
        struct mem_region* regions = r1;
        r1->next = r2;
        r2->next = r3;

        mem_region_merge_empty(regions);

        // Should have free region of size 64
        EXPECT_EQ(1, region_length(regions));
        EXPECT_REGION_EQ(regions, 0, OWNER_NOBODY, 65);

        mem_region_term(regions);
    }
    // Test for merging a 10, 20, a 35, and a 42
    {
        struct mem_region* r1 = mem_region_init(10);
        struct mem_region* r2 = mem_region_init(20);
        struct mem_region* r3 = mem_region_init(35);
        struct mem_region* r4 = mem_region_init(42);
        ASSERT_NE(nullptr, r1);
        ASSERT_NE(nullptr, r2);
        ASSERT_NE(nullptr, r3);
        ASSERT_NE(nullptr, r4);

        // Create the linked list
        struct mem_region* regions = r1;
        r1->next = r2;
        r2->next = r3;
        r3->next = r4;

        mem_region_merge_empty(regions);

        // Should have free region of size 107
        EXPECT_EQ(1, region_length(regions));
        EXPECT_REGION_EQ(regions, 0, OWNER_NOBODY, 107);

        mem_region_term(regions);
    }
}

TEST(PartA, mergeSomeNonEmpty) { 

    // Test for "merging" a 10 with another occupied region
    {
        struct mem_region* r1 = mem_region_init(10);
        struct mem_region* r2 = mem_region_init(20);
        ASSERT_NE(nullptr, r1);
        ASSERT_NE(nullptr, r2);

        // Create the linked list and occupy r2
        struct mem_region* regions = r1;
        r1->next = r2;
        r2->owner = 0xA;

        mem_region_merge_empty(regions);

        // Should have free region of size 10 and owned region of size 20
        EXPECT_EQ(2, region_length(regions));
        EXPECT_REGION_EQ(regions, 0, OWNER_NOBODY, 10);
        EXPECT_REGION_EQ(regions, 1, 0xA, 20);

        mem_region_term(regions);
    }
    // Test for merging a 10, 20, a 35, and a 42 but 35 is occupied
    {
        struct mem_region* r1 = mem_region_init(10);
        struct mem_region* r2 = mem_region_init(20);
        struct mem_region* r3 = mem_region_init(35);
        struct mem_region* r4 = mem_region_init(42);
        ASSERT_NE(nullptr, r1);
        ASSERT_NE(nullptr, r2);
        ASSERT_NE(nullptr, r3);
        ASSERT_NE(nullptr, r4);

        // Create the linked list
        struct mem_region* regions = r1;
        r1->next = r2;
        r2->next = r3;
        r3->next = r4;
        r3->owner = 0xA;

        mem_region_merge_empty(regions);

        // Should have free region of size 30 and owned region of size 35, and free of size 42
        EXPECT_EQ(3, region_length(regions));
        EXPECT_REGION_EQ(regions, 0, OWNER_NOBODY, 30);
        EXPECT_REGION_EQ(regions, 1, 0xA, 35);
        EXPECT_REGION_EQ(regions, 2, OWNER_NOBODY, 42);

        EXPECT_EQ(nullptr, region_at(regions, 2)->next);
        mem_region_term(regions);
    }
}

TEST(PartA, alloc) { 
    // Test alloc small
    {
        struct mem_region* regions = mem_region_init(100);
        ASSERT_NE(nullptr, regions);

        mem_region_alloc(regions, 0xA, 20);

        // Should have a owned region of size 20 and a free of size 80
        EXPECT_EQ(2, region_length(regions));
        EXPECT_REGION_EQ(regions, 0, 0xA, 20);
        EXPECT_REGION_EQ(regions, 1, OWNER_NOBODY, 80);

        mem_region_term(regions);
    }
    // Test alloc 2 smalls
    {
        struct mem_region* regions = mem_region_init(100);
        ASSERT_NE(nullptr, regions);

        mem_region_alloc(regions, 0xA, 20);
        mem_region_alloc(regions, 0xB, 33);

        // Should have a owned region of size 20 and 33, and a free of size 47
        EXPECT_EQ(3, region_length(regions));
        EXPECT_REGION_EQ(regions, 0, 0xA, 20);
        EXPECT_REGION_EQ(regions, 1, 0xB, 33);
        EXPECT_REGION_EQ(regions, 2, OWNER_NOBODY, 47);

        mem_region_term(regions);
    }
}
 
TEST(PartA, allocFree) { 
    // Test alloc small and free it
    {
        struct mem_region* regions = mem_region_init(100);
        ASSERT_NE(nullptr, regions);

        mem_region_alloc(regions, 0xA, 20);
        mem_region_free(regions, 0xA);

        // Should have a free region of size 100
        EXPECT_EQ(1, region_length(regions));
        EXPECT_REGION_EQ(regions, 0, OWNER_NOBODY, 100);

        mem_region_term(regions);
    }
    // Test alloc 2 smalls and free first
    {
        struct mem_region* regions = mem_region_init(100);
        ASSERT_NE(nullptr, regions);

        mem_region_alloc(regions, 0xA, 20);
        mem_region_alloc(regions, 0xB, 33);
        mem_region_free(regions, 0xA);

        // Should have a free region of size 20, owned region of size 33, and a free of size 47
        EXPECT_EQ(3, region_length(regions));
        EXPECT_REGION_EQ(regions, 0, OWNER_NOBODY, 20);
        EXPECT_REGION_EQ(regions, 1, 0xB, 33);
        EXPECT_REGION_EQ(regions, 2, OWNER_NOBODY, 47);

        mem_region_term(regions);
    }
    // Test alloc 2 smalls and free second
    {
        struct mem_region* regions = mem_region_init(100);
        ASSERT_NE(nullptr, regions);

        mem_region_alloc(regions, 0xA, 20);
        mem_region_alloc(regions, 0xB, 33);
        mem_region_free(regions, 0xB);

        // Should have a free region of size 20 and a free of size 80
        EXPECT_EQ(2, region_length(regions));
        EXPECT_REGION_EQ(regions, 0, 0xA, 20);
        EXPECT_REGION_EQ(regions, 1, OWNER_NOBODY, 80);

        mem_region_term(regions);
    }
}
TEST(PartA, allocFreeInvalid) { 
    // Test alloc small and free an invalid entry
    {
        struct mem_region* regions = mem_region_init(100);
        ASSERT_NE(nullptr, regions);

        mem_region_alloc(regions, 0xA, 20);
        mem_region_free(regions, 0xB);

        // Should have a owned region of size 20 and a free of size 80
        EXPECT_EQ(2, region_length(regions));
        EXPECT_REGION_EQ(regions, 0, 0xA, 20);
        EXPECT_REGION_EQ(regions, 1, OWNER_NOBODY, 80);

        mem_region_term(regions);
    }
}
