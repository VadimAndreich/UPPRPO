cmake_minimum_required(VERSION 3.23)
project(Lab_1)

set(CMAKE_CXX_STANDARD 14)

#set(SOURCE_FILES main.cpp)

add_executable(Lab_1 main.cpp)

include_directories(lib)
add_subdirectory(lib)

target_link_libraries(Lab_1 Lab_1_lib)
target_link_libraries(Lab_1 gtest gtest_main)

add_subdirectory(test)