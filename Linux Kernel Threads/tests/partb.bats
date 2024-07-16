setup() {
    DIR="$( cd "$( dirname "$BATS_TEST_FILENAME" )" >/dev/null 2>&1 && pwd )"
    load "$DIR/../extern/test_helper/bats-support/load"
    load "$DIR/../extern/test_helper/bats-assert/load"

    PATH="$DIR/../build/src:$PATH"
}

@test "partb" {
    run partb

    cat "tests/partb_noargs_output.txt" | assert_output -   # Assert if output matches
    assert [ "$status" -eq 1 ]                              # Assert if exit status matches
}
@test "partb 0" {
    run partb 0

    cat "tests/partb_0_output.txt" | assert_output -        # Assert if output matches
    assert [ "$status" -eq 1 ]                              # Assert if exit status matches
}
@test "partb 1" {
    run partb 1

    cat "tests/partb_1_output.txt" | assert_output -        # Assert if output matches
    assert [ "$status" -eq 0 ]                              # Assert if exit status matches
}
@test "partb 2" {
    run partb 2

    cat "tests/partb_2_output.txt" | assert_output -        # Assert if output matches
    assert [ "$status" -eq 0 ]                              # Assert if exit status matches
}
@test "partb 4" {
    run partb 4

    cat "tests/partb_4_output.txt" | assert_output -        # Assert if output matches
    assert [ "$status" -eq 0 ]                              # Assert if exit status matches
}
@test "partb 8" {
    run partb 8

    cat "tests/partb_8_output.txt" | assert_output -        # Assert if output matches
    assert [ "$status" -eq 0 ]                              # Assert if exit status matches
}
@test "partb X" {
    run partb X

    cat "tests/partb_X_output.txt" | assert_output -        # Assert if output matches
    assert [ "$status" -eq 1 ]                              # Assert if exit status matches
}
