setup() {
    DIR="$( cd "$( dirname "$BATS_TEST_FILENAME" )" >/dev/null 2>&1 && pwd )"
    load "$DIR/../extern/test_helper/bats-support/load"
    load "$DIR/../extern/test_helper/bats-assert/load"

    PATH="$DIR/../build/src:$PATH"
}

@test "parta" {
    run parta

    cat "tests/parta_noargs_output.txt" | assert_output -   # Assert if output matches
    assert [ "$status" -eq 1 ]                              # Assert if exit status matches
}
@test "parta 0" {
    run parta 0

    cat "tests/parta_0_output.txt" | assert_output -        # Assert if output matches
    assert [ "$status" -eq 1 ]                              # Assert if exit status matches
}
@test "parta 1" {
    run parta 1

    cat "tests/parta_1_output.txt" | assert_output -        # Assert if output matches
    assert [ "$status" -eq 0 ]                              # Assert if exit status matches
}
@test "parta 2" {
    run parta 2

    output=$(echo "$output" | sort)
    cat "tests/parta_2_output.txt" | assert_output -        # Assert if sorted output matches
    assert [ "$status" -eq 0 ]                              # Assert if exit status matches
}
@test "parta 4" {
    run parta 4

    output=$(echo "$output" | sort)
    cat "tests/parta_4_output.txt" | assert_output -        # Assert if sorted output matches
    assert [ "$status" -eq 0 ]                              # Assert if exit status matches
}
@test "parta 8" {
    run parta 8

    output=$(echo "$output" | sort)
    cat "tests/parta_8_output.txt" | assert_output -        # Assert if sorted output matches
    assert [ "$status" -eq 0 ]                              # Assert if exit status matches
}
@test "parta X" {
    run parta X

    cat "tests/parta_X_output.txt" | assert_output -        # Assert if output matches
    assert [ "$status" -eq 1 ]                              # Assert if exit status matches
}
