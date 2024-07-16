cmake_minimum_required(VERSION 3.21)

project(a9)
find_package(GTest REQUIRED)
set(SANITIZER_CFLAGS -fsanitize=address -fsanitize=undefined)

add_subdirectory(src)
enable_testing()
add_subdirectory(tests)
