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
    printf "    runb1\tRun Part B.1\n"
    printf "    runb2\tRun Part B.2\n"
    printf "    runbextra\tRun Part B.Extra\n"
    printf "    clean\tClear out old files\n"
    printf "    help\tPrint this help message\n"
}
build() {
    cmake -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -G Ninja -B build
    cmake --build build
}
run_tests() {
    env GTEST_COLOR=1 ctest --output-on-failure --timeout 10 --test-dir build --stop-on-failure
}
run_tests_a() {
    env GTEST_COLOR=1 ctest -L A --output-on-failure --timeout 10 --test-dir build --stop-on-failure
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
elif [ "$command" = "runb1" ]
then
    build && ./build/src/partb-1
elif [ "$command" = "runb2" ]
then
    build && ./build/src/partb-2
elif [ "$command" = "runbextra" ]
then
    build && ./build/src/partb-extra
elif [ "$command" = "clean" ]
then
    rm -rf build compile_commands.json
else
    help
fi


