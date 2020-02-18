cmake_minimum_required(VERSION 3.15)
project(differential_evolution)

set(CMAKE_CXX_STANDARD 14)

add_executable(differential_evolution
        src/main.cpp
        lib/mt64.cpp
        lib/mt64.h
        src/func.cpp
        src/func.h
        src/population.h
        src/population.cpp
        src/differential_evolution.cpp
        src/differential_evolution.h
        src/run.h
        src/run.cpp
        src/data_stats.cpp
        src/data_stats.h)