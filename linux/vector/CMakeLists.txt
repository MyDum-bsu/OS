cmake_minimum_required(VERSION 3.23)
project(vector)

set(CMAKE_CXX_STANDARD 14)

add_library(vector SHARED vector.cpp ../enter/dungeon_master.cpp)

include_directories(${CMAKE_SOURCE_DIR}/../number/)
find_library(NUMBER_LIBRARY number ${CMAKE_SOURCE_DIR}/../number/cmake-build-debug)
target_link_libraries(vector LINK_PUBLIC ${NUMBER_LIBRARY})