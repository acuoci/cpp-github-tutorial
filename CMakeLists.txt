cmake_minimum_required(VERSION 3.15)
project(MathLib VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Export compile commands for clang-tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Options
option(ENABLE_COVERAGE "Enable code coverage" OFF)
option(ENABLE_CLANG_TIDY "Enable clang-tidy checks" OFF)
option(ENABLE_CPPCHECK "Enable cppcheck checks" OFF)
option(ENABLE_SANITIZERS "Enable sanitizers (ASan, UBSan)" OFF)

# Library
add_library(mathlib src/mathlib.cpp)
target_include_directories(mathlib PUBLIC src)

# Add coverage flags if enabled
if(ENABLE_COVERAGE)
    message(STATUS "Code coverage enabled")
    
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(mathlib PUBLIC
            --coverage
            -O0        # No optimization for accurate coverage
            -g         # Debug symbols
        )
        target_link_libraries(mathlib PUBLIC --coverage)
    endif()
endif()

# Add sanitizers if enabled
if(ENABLE_SANITIZERS)
    message(STATUS "Sanitizers enabled (ASan + UBSan)")
    
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        set(SANITIZER_FLAGS
            -fsanitize=address
            -fsanitize=undefined
            -fno-omit-frame-pointer
            -g
        )
        
        target_compile_options(mathlib PUBLIC ${SANITIZER_FLAGS})
        target_link_libraries(mathlib PUBLIC ${SANITIZER_FLAGS})
        
        # Additional UBSan options
        target_compile_options(mathlib PUBLIC
            -fno-sanitize-recover=all  # Abort on UB instead of continuing
        )
    else()
        message(WARNING "Sanitizers requested but not supported by this compiler")
    endif()
endif()

# Clang-Tidy integration
if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
    if(CLANG_TIDY_EXE)
        message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
        set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
    else()
        message(WARNING "clang-tidy requested but not found")
    endif()
endif()

# Cppcheck integration
if(ENABLE_CPPCHECK)
    find_program(CPPCHECK_EXE NAMES "cppcheck")
    if(CPPCHECK_EXE)
        message(STATUS "cppcheck found: ${CPPCHECK_EXE}")
        set(CMAKE_CXX_CPPCHECK 
            "${CPPCHECK_EXE}"
            "--enable=all"
            "--inconclusive"
            "--force"
            "--inline-suppr"
            "--suppressions-list=${CMAKE_SOURCE_DIR}/.cppcheck-suppressions"
            "--error-exitcode=0"  # Don't fail build, just warn
        )
    else()
        message(WARNING "cppcheck requested but not found")
    endif()
endif()

# Testing
enable_testing()
add_subdirectory(tests)

# Benchmarking
option(BUILD_BENCHMARKS "Build performance benchmarks" ON)
if(BUILD_BENCHMARKS)
    message(STATUS "Building benchmarks")
    add_subdirectory(benchmarks)
else()
    message(STATUS "Skipping benchmarks")
endif()