cmake_minimum_required(VERSION 3.15)
project(cuckoo_search)

set(CMAKE_CXX_STANDARD 14)

add_executable(cuckoo_search
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
        src/cuckoo_search.cpp
        src/cuckoo_search.h src/cuckoo_search_gaussian.cpp src/cuckoo_search_gaussian.h src/cuckoo_search_ecs.cpp src/cuckoo_search_ecs.h)