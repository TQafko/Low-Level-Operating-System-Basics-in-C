#include <gtest/gtest.h>
#include "partb.h"

TEST(PartB, splitEcho) { 
    const char* argv[] = { "partc", "echo", NULL };
    char* args1[] = { NULL, NULL };
    char* args2[] = { NULL, NULL };
    split_args(2, (char**)argv, args1, args2);

    ASSERT_STREQ("echo", args1[0]);
    ASSERT_EQ(nullptr, args1[1]);

    ASSERT_EQ(nullptr, args2[0]);
}
TEST(PartB, splitEchoHello) { 
    const char* argv[] = { "partc", "echo", "Hello", NULL };
    char* args1[] = { NULL, NULL, NULL };
    char* args2[] = { NULL, NULL, NULL };
    split_args(3, (char**)argv, args1, args2);

    ASSERT_STREQ("echo", args1[0]);
    ASSERT_STREQ("Hello", args1[1]);
    ASSERT_EQ(nullptr, args1[2]);

    ASSERT_EQ(nullptr, args2[0]);
}
TEST(PartB, splitEchoHelloBoston) { 
    const char* argv[] = { "partc", "echo", "Hello", "Boston", NULL };
    char* args1[] = { NULL, NULL, NULL, NULL };
    char* args2[] = { NULL, NULL, NULL, NULL };
    split_args(4, (char**)argv, args1, args2);

    ASSERT_STREQ("echo", args1[0]);
    ASSERT_STREQ("Hello", args1[1]);
    ASSERT_STREQ("Boston", args1[2]);
    ASSERT_EQ(nullptr, args1[3]);

    ASSERT_EQ(nullptr, args2[0]);
}
TEST(PartB, splitEchoSort) { 
    const char* argv[] = { "partc", "echo", ":", "sort", NULL };
    char* args1[] = { NULL, NULL, NULL, NULL };
    char* args2[] = { NULL, NULL, NULL, NULL };
    split_args(4, (char**)argv, args1, args2);

    ASSERT_STREQ("echo", args1[0]);
    ASSERT_EQ(nullptr, args1[1]);

    ASSERT_STREQ("sort", args2[0]);
    ASSERT_EQ(nullptr, args2[1]);
}
TEST(PartB, splitEchoSort2) { 
    const char* argv[] = { "partc", "echo", ":", "sort", "-r", NULL };
    char* args1[] = { NULL, NULL, NULL, NULL, NULL };
    char* args2[] = { NULL, NULL, NULL, NULL, NULL };
    split_args(5, (char**)argv, args1, args2);

    ASSERT_STREQ("echo", args1[0]);
    ASSERT_EQ(nullptr, args1[1]);

    ASSERT_STREQ("sort", args2[0]);
    ASSERT_STREQ("-r", args2[1]);
    ASSERT_EQ(nullptr, args2[2]);
}
TEST(PartB, splitEchoSort2_2) { 
    const char* argv[] = { "partc", "echo", "Hello", ":", "sort", "-r", NULL };
    char* args1[] = { NULL, NULL, NULL, NULL, NULL, NULL };
    char* args2[] = { NULL, NULL, NULL, NULL, NULL, NULL };
    split_args(6, (char**)argv, args1, args2);

    ASSERT_STREQ("echo", args1[0]);
    ASSERT_STREQ("Hello", args1[1]);
    ASSERT_EQ(nullptr, args1[2]);

    ASSERT_STREQ("sort", args2[0]);
    ASSERT_STREQ("-r", args2[1]);
    ASSERT_EQ(nullptr, args2[2]);
}

