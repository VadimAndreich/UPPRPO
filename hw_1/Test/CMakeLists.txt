cmake_minimum_required(VERSION 3.22)
project(Tests)

add_subdirectory(lib/googletest-1.14.0)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Tests tests.cpp)

target_link_libraries(Tests Lab_1_lib)
target_link_libraries(Tests gtest gtest_main)
