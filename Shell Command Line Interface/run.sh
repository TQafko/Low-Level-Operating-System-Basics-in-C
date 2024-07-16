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
    printf "    testb\tRun tests for Part B\n"
    printf "    clean\tClear out old files\n"
    printf "    help\tPrint this help message\n"
}
build() {
    cmake -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -G Ninja -B build
    cmake --build build
}
run_tests() {
    export BATS_TEST_TIMEOUT=10
    ./extern/bats/bin/bats tests/parta.bats
    ctest --timeout 10 --test-dir build && ./extern/bats/bin/bats tests/partb.bats
}
run_tests_a() {
    export BATS_TEST_TIMEOUT=10
    ./extern/bats/bin/bats tests/parta.bats
}
run_tests_b() {
    export BATS_TEST_TIMEOUT=10
    ctest --timeout 10 --test-dir build && ./extern/bats/bin/bats tests/partb.bats
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
elif [ "$command" = "testb" ]
then
    build && run_tests_b
elif [ "$command" = "clean" ]
then
    rm -rf build compile_commands.json
else
    help
fi


