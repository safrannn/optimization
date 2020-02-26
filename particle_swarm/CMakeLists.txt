cmake_minimum_required(VERSION 3.15)
project(particle_swarm)

set(CMAKE_CXX_STANDARD 14)

add_executable(particle_swarm
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
        src/particle_swarm.cpp
        src/particle_swarm.h)