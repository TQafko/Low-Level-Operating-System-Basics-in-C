setup() {
    DIR="$( cd "$( dirname "$BATS_TEST_FILENAME" )" >/dev/null 2>&1 && pwd )"
    load "$DIR/../extern/test_helper/bats-support/load"
    load "$DIR/../extern/test_helper/bats-assert/load"

    PATH="$DIR/../build/src:$PATH"
}
@test "parta_main" {
    run parta_main

    cat "tests/parta_noargs_output.txt" | assert_output -   # Assert if output matches
    assert [ "$status" -eq 1 ]                              # Assert if exit status matches
}
@test "parta_main echo" {
    run parta_main /usr/bin/echo

    cat "tests/parta_echo_output.txt" | assert_output -     # Assert if output matches
}
@test "parta_main echo Hello" {
    run parta_main /usr/bin/echo Hello

    cat "tests/parta_echoHello_output.txt" | assert_output - # Assert if output matches
}
@test "parta_main echo Goodbye" {
    run parta_main /usr/bin/echo Goodbye

    cat "tests/parta_echoGoodbye_output.txt" | assert_output - # Assert if output matches
}
@test "parta_main echo Hello Boston" {
    run parta_main /usr/bin/echo Hello Boston

    cat "tests/parta_echoHelloBoston_output.txt" | assert_output - # Assert if output matches
}
@test "parta_main /usr/bin/head -n1 tests/cities.csv" {
    run parta_main /usr/bin/head -n1 tests/cities.csv

    cat "tests/parta_head1_cities.txt" | assert_output - # Assert if output matches
}
@test "parta_main /usr/bin/head -n4 tests/cities.csv" {
    run parta_main /usr/bin/head -n4 tests/cities.csv

    cat "tests/parta_head4_cities.txt" | assert_output - # Assert if output matches
}
@test "parta_main /usr/bin/tail -n1 tests/cities.csv" {
    run parta_main /usr/bin/tail -n1 tests/cities.csv

    cat "tests/parta_tail1_cities.txt" | assert_output - # Assert if output matches
}
@test "parta_main /usr/bin/tail -n4 tests/cities.csv" {
    run parta_main /usr/bin/tail -n4 tests/cities.csv

    cat "tests/parta_tail4_cities.txt" | assert_output - # Assert if output matches
}
