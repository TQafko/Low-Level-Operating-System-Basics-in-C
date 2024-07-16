#include <gtest/gtest.h>
#include "parta.h"

TEST(PartA, initTerm) { 
    ASSERT_EQ(nullptr, init_procs(NULL, 0));

    struct pcb* procs = NULL;

    int bursts5[] = { 5 };
    procs = init_procs(bursts5, 1);
    ASSERT_NE(nullptr, procs);
    ASSERT_EQ(0, procs[0].pid);
    ASSERT_EQ(5, procs[0].burst_left);
    ASSERT_EQ(0, procs[0].wait);
    free(procs);

    int bursts5_8[] = { 5, 8 };
    procs = init_procs(bursts5_8, 2);
    ASSERT_NE(nullptr, procs);
    ASSERT_EQ(0, procs[0].pid);
    ASSERT_EQ(5, procs[0].burst_left);
    ASSERT_EQ(0, procs[0].wait);
    ASSERT_EQ(1, procs[1].pid);
    ASSERT_EQ(8, procs[1].burst_left);
    ASSERT_EQ(0, procs[1].wait);
    free(procs);


    int bursts5_8_2[] = { 5, 8, 2 };
    procs = init_procs(bursts5_8_2, 3);
    ASSERT_NE(nullptr, procs);
    ASSERT_EQ(0, procs[0].pid);
    ASSERT_EQ(5, procs[0].burst_left);
    ASSERT_EQ(0, procs[0].wait);
    ASSERT_EQ(1, procs[1].pid);
    ASSERT_EQ(8, procs[1].burst_left);
    ASSERT_EQ(0, procs[1].wait);
    ASSERT_EQ(2, procs[2].pid);
    ASSERT_EQ(2, procs[2].burst_left);
    ASSERT_EQ(0, procs[2].wait);
    free(procs);
}
TEST(PartA, test_fcfs_next) { 
    ASSERT_EQ(-1, fcfs_next(0, NULL, 0));

    // Set up PCBs with burst 5
    struct pcb procs1[] = { { 0, 5, 0 } };
    ASSERT_EQ(-1, fcfs_next(0, procs1, 1));

    // Set up PCBs with burst 5 and 8
    struct pcb procs2[] = { { 0, 5, 0 }, { 1, 8, 0} };
    ASSERT_EQ(1, fcfs_next(0, procs2, 2));
    ASSERT_EQ(-1, fcfs_next(1, procs2, 2));
}
TEST(PartA, test_fcfs) { 
    int bursts5[] = { 5 };
    ASSERT_DOUBLE_EQ(0, fcfs_avg_wait(bursts5, 1));

    int bursts5_8[] = { 5, 8 };
    ASSERT_DOUBLE_EQ(2.5, fcfs_avg_wait(bursts5_8, 2));

    int bursts5_8_2[] = { 5, 8, 2 };
    ASSERT_DOUBLE_EQ((5.0+13.0)/3.0, fcfs_avg_wait(bursts5_8_2, 3));
}
TEST(PartA, test_rr_next) { 
    ASSERT_EQ(-1, rr_next(0, NULL, 0));

    // Set up PCBs with burst 0
    struct pcb procs0[] = { { 0, 0, 0 } };
    ASSERT_EQ(-1, rr_next(0, procs0, 1));

    // Set up PCBs with burst 0 (current) and 8
    struct pcb procs0_8[] = { { 0, 0, 0 }, { 1, 8, 0} };
    ASSERT_EQ(1, rr_next(0, procs0_8, 2));

    // Set up PCBs with burst 2 (current) and 8
    struct pcb procs2_8[] = { { 0, 2, 0 }, { 1, 8, 0} };
    ASSERT_EQ(1, rr_next(0, procs2_8, 2));

    // Set up PCBs with burst 2 and 4 (current) 
    struct pcb procs2_4[] = { { 0, 2, 0 }, { 1, 4, 0} };
    ASSERT_EQ(0, rr_next(1, procs2_4, 2));

    // Set up PCBs with burst 4, burst 0 (current) and 8
    struct pcb procs4_0_8[] = { { 0, 4, 0 }, {1, 0, 0}, { 2, 8, 0} };
    ASSERT_EQ(2, rr_next(1, procs4_0_8, 3));
    // If current was 8 instead
    ASSERT_EQ(0, rr_next(2, procs4_0_8, 3));
    // If current was 0 instead, skip the empty p1
    ASSERT_EQ(2, rr_next(0, procs4_0_8, 3));
}
TEST(PartA, test_rr_tq100) { 
    int bursts5[] = { 5 };
    ASSERT_DOUBLE_EQ(0, rr_avg_wait(bursts5, 1, 100));

    int bursts5_8[] = { 5, 8 };
    ASSERT_DOUBLE_EQ(2.5, rr_avg_wait(bursts5_8, 2, 100));

    int bursts5_8_2[] = { 5, 8, 2 };
    ASSERT_DOUBLE_EQ((5+13)/3.0, rr_avg_wait(bursts5_8_2, 3, 100));
}
TEST(PartA, test_rr_tq4) { 
    int bursts5[] = { 5 };
    ASSERT_DOUBLE_EQ(0, rr_avg_wait(bursts5, 1, 4));

    int bursts5_8[] = { 5, 8 };
    ASSERT_DOUBLE_EQ((4 + 4 + 1) / 2.0, rr_avg_wait(bursts5_8, 2, 4));

    int bursts5_8_2[] = { 5, 8, 2 };
    ASSERT_DOUBLE_EQ((6 + 3 + 4 + 8) / 3.0, rr_avg_wait(bursts5_8_2, 3, 4));
}

