cmake_minimum_required(VERSION 3.10)

project(MyCppProject)

# Add include directories
include_directories(include)

# Add the main executable
add_executable(MyCppProject src/main.cpp src/lib.cpp)

# Include the tests subdirectory
add_subdirectory(tests)
