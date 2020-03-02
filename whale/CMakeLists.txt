cmake_minimum_required(VERSION 3.15)
project(whale)

set(CMAKE_CXX_STANDARD 14)

add_executable(whale
        src/main.cpp
        lib/mt64.cpp
        lib/mt64.h
        src/func.cpp
        src/func.h
        src/population.h
        src/population.cpp
        src/run.h
        src/run.cpp
        src/data_stats.cpp
        src/data_stats.h
        src/whale.cpp
        src/whale.h)