cmake_minimum_required(VERSION 3.15)
project(functions)

set(CMAKE_CXX_STANDARD 14)

include_directories(lib)
include_directories(out)
include_directories(src)

add_executable(functions
        lib/mt64.cpp
        lib/mt64.h
        out/func_fx.csv
        out/func_result.csv
        src/func.cpp
        src/func.h
        src/result.cpp
        src/result.h
        src/util.cpp
        src/util.h
        main.cpp)
