setup() {
    DIR="$( cd "$( dirname "$BATS_TEST_FILENAME" )" >/dev/null 2>&1 && pwd )"
    load "$DIR/../extern/test_helper/bats-support/load"
    load "$DIR/../extern/test_helper/bats-assert/load"

    PATH="$DIR/../build/src:$PATH"
}
@test "parta_main" {
    run parta_main

    cat "tests/parta_usage_output.txt" | assert_output -   # Assert if output matches
    assert [ "$status" -eq 1 ]                             # Assert if exit status matches
}
@test "parta_main fcfs" {
    run parta_main fcfs

    cat "tests/parta_usage_output.txt" | assert_output -   # Assert if output matches
    assert [ "$status" -eq 1 ]                             # Assert if exit status matches
}
@test "parta_main rr" {
    run parta_main rr

    cat "tests/parta_usage_output.txt" | assert_output -   # Assert if output matches
    assert [ "$status" -eq 1 ]                             # Assert if exit status matches
}
@test "parta_main sjf" {
    run parta_main sjf

    cat "tests/parta_usage_output.txt" | assert_output -   # Assert if output matches
    assert [ "$status" -eq 1 ]                             # Assert if exit status matches
}

@test "parta_main fcfs 5" {
    run parta_main fcfs 5

    cat "tests/parta_fcfs5_output.txt" | assert_output -   # Assert if output matches
    assert [ "$status" -eq 0 ]                             # Assert if exit status matches
}


