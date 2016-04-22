cmake_minimum_required(VERSION 3.5)
project(Praktikum2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -march=native")

add_subdirectory(src)
add_subdirectory(test)
