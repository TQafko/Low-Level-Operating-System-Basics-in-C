set(WARNING_CFLAGS -Wall -Wextra -Werror -Wfatal-errors -Wshadow -Wvla -Wfloat-conversion -Wfloat-equal)
set(NOWARN_CFLAGS -Wno-unused -Wno-sign-conversion -Wno-unused-parameter -Wno-unknown-warning-option)
set(MY_CFLAGS ${WARNING_CFLAGS} ${SANITIZER_CFLAGS} ${NOWARN_CFLAGS})

find_package(Threads REQUIRED)

foreach(PART parta partb partc)
    add_executable(${PART} ${PART}.c ${PART}.h)
    target_include_directories(${PART} PUBLIC .)
    target_link_libraries(${PART} Threads::Threads)
    target_compile_options(${PART} PRIVATE ${MY_CFLAGS})
    target_compile_features(${PART} PUBLIC c_std_17)
    target_link_options(${PART} PUBLIC ${SANITIZER_CFLAGS})
endforeach()

# Additional libraries for part c
target_include_directories(partc PUBLIC ${CMAKE_SOURCE_DIR}/extern/include)
target_link_libraries(partc m)

# The sample program
add_executable(partc-sample partc-sample.c partc.h)
target_include_directories(partc-sample PUBLIC . ${CMAKE_SOURCE_DIR}/extern/include)
target_link_libraries(partc-sample m Threads::Threads)
target_compile_options(partc-sample PRIVATE ${MY_CFLAGS})
target_compile_features(partc-sample PUBLIC c_std_17)
target_link_options(partc-sample PUBLIC ${SANITIZER_CFLAGS})
