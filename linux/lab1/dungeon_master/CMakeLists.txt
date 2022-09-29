cmake_minimum_required(VERSION 3.23)
project(dungeon_master)

set(CMAKE_CXX_STANDARD 14)

add_executable(dungeon_master dungeon_master.cpp)

include_directories(${CMAKE_SOURCE_DIR}/../number/)
find_library(NUMBER_LIBRARY number ${CMAKE_SOURCE_DIR}/../number/cmake-build-debug)
target_link_libraries(dungeon_master LINK_PUBLIC ${NUMBER_LIBRARY})

include_directories(${CMAKE_SOURCE_DIR}/../vector/)
find_library(VECTOR_LIBRARY vector ${CMAKE_SOURCE_DIR}/../vector/cmake-build-debug)
target_link_libraries(dungeon_master LINK_PUBLIC ${VECTOR_LIBRARY})