set(WARNING_CFLAGS -Wall -Wextra -Wuninitialized -Wshadow -Wvla -Wfloat-equal -Walloc-zero)
set(NOWARN_CFLAGS -Wno-unused -Wno-sign-conversion -Wno-sign-compare)
set(MY_CFLAGS -ggdb -Werror -Wfatal-errors ${WARNING_CFLAGS} ${SANITIZER_CFLAGS} ${NOWARN_CFLAGS})

add_library(partb OBJECT partb.c partb.h)
target_include_directories(partb PUBLIC .)
target_compile_options(partb PRIVATE ${MY_CFLAGS})
target_compile_features(partb PUBLIC c_std_17)
target_link_options(partb PUBLIC ${SANITIZER_CFLAGS})

foreach(PART_MAIN parta_main partb_main)
    add_executable(${PART_MAIN} ${PART_MAIN}.c)
    target_compile_options(${PART_MAIN} PRIVATE ${MY_CFLAGS})
    target_compile_features(${PART_MAIN} PUBLIC c_std_17)
    target_link_options(${PART_MAIN} PUBLIC ${SANITIZER_CFLAGS})
endforeach()

target_link_libraries(partb_main PRIVATE partb)
