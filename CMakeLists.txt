cmake_minimum_required(VERSION 3.25)
project(gpu_usage_tracker C)

set(CMAKE_C_STANDARD 11)

add_executable(gpu_usage_tracker main.c reader.h Analyzer.cpp Analyzer.h)
