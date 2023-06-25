cmake_minimum_required(VERSION 3.5)

project(cpu_usage_tracker C)
set(CMAKE_C_STANDARD 11)

if (DEFINED ENV{CC})
    set(CMAKE_C_COMPILER $ENV{CC})
else()
    set(CMAKE_C_COMPILER gcc)
endif()

set(FILES
        main.c
        reader.c
        analyzer.c
        printer.c
        watchdog.c
        sigterm.c
        logger.c
        )

add_executable(cpu_usage_tracker ${FILES})

set(TEST
        main_valgrind.c
        reader.c
        analyzer.c
        printer.c
        watchdog.c
        sigterm.c
        logger.c
        )

add_executable(valgrind_test ${TEST})


if(CMAKE_C_COMPILER_ID MATCHES "Clang")
    target_compile_options(cpu_usage_tracker PRIVATE -Weverything -Werror)
endif()

if(CMAKE_C_COMPILER_ID MATCHES "GNU")
    target_compile_options(cpu_usage_tracker PRIVATE -Wall -Wextra -Werror)
endif()



