cmake_minimum_required(VERSION 3.15)
project(MathLib VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Library
add_library(mathlib src/mathlib.cpp)
target_include_directories(mathlib PUBLIC src)

# Tests
enable_testing()
add_executable(test_basic tests/test_basic.cpp)
target_link_libraries(test_basic mathlib)
add_test(NAME BasicTest COMMAND test_basic)