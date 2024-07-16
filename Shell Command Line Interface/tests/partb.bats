setup() {
    DIR="$( cd "$( dirname "$BATS_TEST_FILENAME" )" >/dev/null 2>&1 && pwd )"
    load "$DIR/../extern/test_helper/bats-support/load"
    load "$DIR/../extern/test_helper/bats-assert/load"

    PATH="$DIR/../build/src:$PATH"
}
@test "partb_main" {
    run partb_main

    cat "tests/partb_noargs_output.txt" | assert_output -   # Assert if output matches
    assert [ "$status" -eq 1 ]                              # Assert if exit status matches
}
@test "partb_main echo" {
    run partb_main /usr/bin/echo

    cat "tests/parta_echo_output.txt" | assert_output -     # Assert if output matches
}
@test "partb_main echo Hello" {
    run partb_main /usr/bin/echo Hello

    cat "tests/parta_echoHello_output.txt" | assert_output - # Assert if output matches
}
@test "partb_main echo Goodbye" {
    run partb_main /usr/bin/echo Goodbye

    cat "tests/parta_echoGoodbye_output.txt" | assert_output - # Assert if output matches
}
@test "partb_main echo Hello Boston" {
    run partb_main /usr/bin/echo Hello Boston

    cat "tests/parta_echoHelloBoston_output.txt" | assert_output - # Assert if output matches
}
@test "partb_main /usr/bin/head -n1 tests/cities.csv" {
    run partb_main /usr/bin/head -n1 tests/cities.csv

    cat "tests/parta_head1_cities.txt" | assert_output - # Assert if output matches
}
@test "partb_main /usr/bin/head -n4 tests/cities.csv" {
    run partb_main /usr/bin/head -n4 tests/cities.csv

    cat "tests/parta_head4_cities.txt" | assert_output - # Assert if output matches
}
@test "partb_main /usr/bin/tail -n1 tests/cities.csv" {
    run partb_main /usr/bin/tail -n1 tests/cities.csv

    cat "tests/parta_tail1_cities.txt" | assert_output - # Assert if output matches
}
@test "partb_main /usr/bin/tail -n4 tests/cities.csv" {
    run partb_main /usr/bin/tail -n4 tests/cities.csv

    cat "tests/parta_tail4_cities.txt" | assert_output - # Assert if output matches
}
@test "partb_main tail -n1 cities.csv : head -n1" {
    run partb_main /usr/bin/tail -n1 tests/cities.csv : /usr/bin/head -n1

    cat "tests/parta_t1h1_cities.txt" | assert_output - # Assert if output matches
}
@test "partb_main head -n1 cities.csv : tail -n1" {
    run partb_main /usr/bin/head -n1 tests/cities.csv : /usr/bin/tail -n1

    cat "tests/parta_h1t1_cities.txt" | assert_output - # Assert if output matches
}
@test "partb_main tail -n4 cities.csv : head -n1" {
    run partb_main /usr/bin/tail -n4 tests/cities.csv : /usr/bin/head -n1

    cat "tests/parta_t4h1_cities.txt" | assert_output - # Assert if output matches
}
