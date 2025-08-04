cmake_minimum_required(VERSION 3.31)
project(wci2)

set(CMAKE_CXX_STANDARD 26)

add_executable(wci2 main.cpp
        buffer.h
        misc.h
        error.h
        buffer.cpp
        common.h
        common.cpp
        error.cpp)
