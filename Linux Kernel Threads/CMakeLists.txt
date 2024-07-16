cmake_minimum_required(VERSION 3.21)

project(a5)

set(SANITIZER_CFLAGS -fsanitize=address -fsanitize=undefined)

add_subdirectory(src)

