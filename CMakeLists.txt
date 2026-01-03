cmake_minimum_required(VERSION 3.15)
project(MathLib VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Option for code coverage
option(ENABLE_COVERAGE "Enable code coverage" OFF)

# Library
add_library(mathlib src/mathlib.cpp)
target_include_directories(mathlib PUBLIC src)

# Add coverage flags if enabled
if(ENABLE_COVERAGE)
    message(STATUS "Code coverage enabled")
    
    # Coverage flags for GCC/Clang
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        # Add flags to library
        target_compile_options(mathlib PUBLIC
            --coverage
            -O0        # No optimization for accurate coverage
            -g         # Debug symbols
        )
        target_link_libraries(mathlib PUBLIC --coverage)
        
        # Alternative: use target_link_options if CMake >= 3.13
        # target_link_options(mathlib PUBLIC --coverage)
    endif()
endif()

# Testing
enable_testing()
add_subdirectory(tests)

# Benchmarking (optional, can be disabled with -DBUILD_BENCHMARKS=OFF)
option(BUILD_BENCHMARKS "Build performance benchmarks" ON)
if(BUILD_BENCHMARKS)
    message(STATUS "Building benchmarks")
    add_subdirectory(benchmarks)
else()
    message(STATUS "Skipping benchmarks")
endif()