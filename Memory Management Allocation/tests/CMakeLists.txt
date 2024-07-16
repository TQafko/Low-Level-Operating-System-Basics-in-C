add_executable(test_a test_a.cpp)

target_link_libraries(test_a PRIVATE parta GTest::gtest_main)
target_compile_options(test_a PUBLIC -ggdb ${SANITIZER_CFLAGS})
target_include_directories(test_a PRIVATE .)
target_link_options(test_a PUBLIC ${SANITIZER_CFLAGS})
target_compile_features(test_a PUBLIC cxx_std_17)

gtest_discover_tests(test_a PROPERTIES LABELS "A")
