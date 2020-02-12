cmake_minimum_required(VERSION 3.15)
project(genetic_algorithm)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(lib)
include_directories(out)
include_directories(src)

add_executable(genetic_algorithm
        lib/mt64.cpp
        lib/mt64.h
        src/func.cpp
        src/func.h
        src/genetic_algorithm.cpp
        src/genetic_algorithm.h
        src/population.cpp
        src/population.h
        src/run.cpp
        src/run.h
        src/data_stats.cpp
        src/data_stats.h
        main.cpp )
