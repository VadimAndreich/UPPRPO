# Enable testing
enable_testing()

# Add the test executable
add_executable(runTests tests.cpp ../src/lib.cpp)

# Link test executable against gtest & gtest_main
target_link_libraries(runTests gtest gtest_main)

# Add test
add_test(NAME MyTest COMMAND runTests)
