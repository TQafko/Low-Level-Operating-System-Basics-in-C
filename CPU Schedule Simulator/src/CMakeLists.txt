set(WARNING_CFLAGS -Wall -Wextra -Wuninitialized -Wshadow -Wvla -Wfloat-equal)
set(NOWARN_CFLAGS -Wno-unused -Wno-unused-parameter -Wno-sign-conversion -Wno-sign-compare)
set(MY_CFLAGS -ggdb -Werror -Wfatal-errors ${WARNING_CFLAGS} ${SANITIZER_CFLAGS} ${NOWARN_CFLAGS})

add_library(parta OBJECT parta.c parta.h)
target_include_directories(parta PUBLIC .)
target_compile_options(parta PRIVATE ${MY_CFLAGS})
target_compile_features(parta PUBLIC c_std_17)
target_link_options(parta PUBLIC ${SANITIZER_CFLAGS})

foreach(PART_MAIN parta_main)
    add_executable(${PART_MAIN} ${PART_MAIN}.c)
    target_compile_options(${PART_MAIN} PRIVATE ${MY_CFLAGS})
    target_compile_features(${PART_MAIN} PUBLIC c_std_17)
    target_link_options(${PART_MAIN} PUBLIC ${SANITIZER_CFLAGS})
endforeach()

target_link_libraries(parta_main PRIVATE parta)
