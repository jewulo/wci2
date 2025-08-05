cmake_minimum_required(VERSION 3.31)
project(wci2)

set(CMAKE_CXX_STANDARD 26)

add_executable(wci2 main.cpp
        misc.h
        error.h
        common.h
        common.cpp
        error.cpp
        buffer.cpp
        buffer.h
)
