#include <gtest/gtest.h>
#include "parta.h"

TEST(PartA, find_cycle_false) { 
    ASSERT_FALSE(find_cycle(NULL, 0));
    {
        int wait_for[] = {-1};
        ASSERT_FALSE(find_cycle(wait_for, 1));
    }

    {
        int wait_for[] = {-1, -1};
        ASSERT_FALSE(find_cycle(wait_for, 2));
    }
    {
        int wait_for[] = {1, -1, 0};
        ASSERT_FALSE(find_cycle(wait_for, 3));
    }
    {
        int wait_for[] = {1, -1, 0};
        ASSERT_FALSE(find_cycle(wait_for, 3));
    }
}

TEST(PartA, find_cycle_true) { 
    {
        int wait_for[] = {1, 0};
        ASSERT_TRUE(find_cycle(wait_for, 2));
    }
    {
        int wait_for[] = {1, 0, 1};
        ASSERT_TRUE(find_cycle(wait_for, 3));
    }
    {
        int wait_for[] = {1, 2, 1};
        ASSERT_TRUE(find_cycle(wait_for, 3));
    }
    {
        int wait_for[] = {1, 0, 0};
        ASSERT_TRUE(find_cycle(wait_for, 3));
    }
}

