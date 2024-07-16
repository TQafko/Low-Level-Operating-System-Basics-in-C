setup() {
    DIR="$( cd "$( dirname "$BATS_TEST_FILENAME" )" >/dev/null 2>&1 && pwd )"
    load "$DIR/../extern/test_helper/bats-support/load"
    load "$DIR/../extern/test_helper/bats-assert/load"
    load "$DIR/../extern/test_helper/bats-file/load"

    PATH="$DIR/../build/src:$PATH"
}

@test "partc" {
    run partc

    cat "tests/partc_noargs_output.txt" | assert_output -   # Assert if output matches
    assert [ "$status" -eq 1 ]                              # Assert if exit status matches
}
@test "partc tests/red_line.png out.png 1" {
    rm -f "out.png"
    run partc tests/red_line.png out.png 1

    assert_exists "out.png"
    assert_files_equal "out.png" "tests/red_line.out.png"
}
@test "partc tests/red_line.png out.png 2" {
    rm -f "out.png"
    run partc tests/red_line.png out.png 2

    assert_exists "out.png"
    assert_files_equal "out.png" "tests/red_line.out.png"
}
@test "partc tests/red_line.png out.png 4" {
    rm -f "out.png"
    run partc tests/red_line.png out.png 4

    assert_exists "out.png"
    assert_files_equal "out.png" "tests/red_line.out.png"
}
@test "partc tests/red_box.png out.png 1" {
    rm -f "out.png"
    run partc tests/red_box.png out.png 1

    assert_exists "out.png"
    assert_files_equal "out.png" "tests/red_box.out.png"
}
@test "partc tests/red_box.png out.png 2" {
    rm -f "out.png"
    run partc tests/red_box.png out.png 2

    assert_exists "out.png"
    assert_files_equal "out.png" "tests/red_box.out.png"
}
@test "partc tests/red_box.png out.png 4" {
    rm -f "out.png"
    run partc tests/red_box.png out.png 4

    assert_exists "out.png"
    assert_files_equal "out.png" "tests/red_box.out.png"
}
@test "partc tests/A.png out.png 1" {
    rm -f "out.png"
    run partc tests/A.png out.png 1

    assert_exists "out.png"
    assert_files_equal "out.png" "tests/A.out.png"
}
@test "partc tests/A.png out.png 2" {
    rm -f "out.png"
    run partc tests/A.png out.png 2

    assert_exists "out.png"
    assert_files_equal "out.png" "tests/A.out.png"
}
@test "partc tests/A.png out.png 4" {
    rm -f "out.png"
    run partc tests/A.png out.png 4

    assert_exists "out.png"
    assert_files_equal "out.png" "tests/A.out.png"
}
@test "partc tests/pencils.png out.png 1" {
    rm -f "out.png"
    run partc tests/pencils.png out.png 1

    assert_exists "out.png"
    assert_files_equal "out.png" "tests/pencils.out.png"
}
@test "partc tests/pencils.png out.png 2" {
    rm -f "out.png"
    run partc tests/pencils.png out.png 2

    assert_exists "out.png"
    assert_files_equal "out.png" "tests/pencils.out.png"
}
@test "partc tests/pencils.png out.png 4" {
    rm -f "out.png"
    run partc tests/pencils.png out.png 4

    assert_exists "out.png"
    assert_files_equal "out.png" "tests/pencils.out.png"
}
