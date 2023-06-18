cmake_minimum_required(VERSION 3.25)

SET(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Werror")

project(gpu_usage_tracker C)

add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

set(CMAKE_C_STANDARD 11)

add_executable(gpu_usage_tracker main.c reader.h analyzer.c analyzer.h printer.c printer.h global_variables.h reader.c watchdog.c watchdog.h sigterm.c sigterm.h logger.c logger.h)
