#!/bin/sh

command="$1"

help() {
    echo   "USAGE:"
    echo   "  $0 <COMMANDS>"
    echo   ""
    echo   "  COMMANDS:"
    printf "    build\tBuild code\n"
    printf "    test\tRun all tests\n"
    printf "    testa\tRun tests for Part A\n"
    printf "    clean\tClear out old files\n"
    printf "    help\tPrint this help message\n"
}
build() {
    cmake -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -G Ninja -B build
    cmake --build build
}
run_tests() {
    ctest --output-on-failure --timeout 10 --test-dir build
}
run_tests_a() {
    ctest --output-on-failure --timeout 10 --test-dir build -L A
}

if [ "$command" = "help" ]
then
    help
elif [ "$command" = "build" ]
then
    build
elif [ "$command" = "test" ]
then
    build && run_tests
elif [ "$command" = "testa" ]
then
    build && run_tests_a
elif [ "$command" = "clean" ]
then
    rm -rf build compile_commands.json
else
    help
fi


