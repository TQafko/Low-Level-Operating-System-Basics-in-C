add_executable(test_b test_b.cpp)

target_link_libraries(test_b PRIVATE partb GTest::gtest_main)
target_compile_options(test_b PUBLIC -ggdb ${SANITIZER_CFLAGS})
target_include_directories(test_b PRIVATE .)
target_link_options(test_b PUBLIC ${SANITIZER_CFLAGS})
target_compile_features(test_b PUBLIC cxx_std_17)

gtest_discover_tests(test_b PROPERTIES LABELS "B")
