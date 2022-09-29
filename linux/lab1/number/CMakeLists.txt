cmake_minimum_required(VERSION 3.23)
project(number)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-fpic)
add_library(number number.cpp)
