set(WARNING_CFLAGS -Wall -Wextra -Wuninitialized -Wshadow -Wvla -Wfloat-equal)
set(NOWARN_CFLAGS -Wno-unused -Wno-sign-conversion -Wno-sign-compare)
set(MY_CFLAGS -ggdb -Werror -Wfatal-errors ${WARNING_CFLAGS} ${SANITIZER_CFLAGS} ${NOWARN_CFLAGS})

foreach(PART parta)
    add_library(${PART} OBJECT ${PART}.c ${PART}.h)
    target_include_directories(${PART} PUBLIC .)
    target_compile_options(${PART} PRIVATE ${MY_CFLAGS})
    target_compile_features(${PART} PUBLIC c_std_17)
    target_link_options(${PART} PUBLIC ${SANITIZER_CFLAGS})
endforeach()

