cmake_minimum_required(VERSION 3.15)

# Set vcpkg toolchain file before project()
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "")
endif()

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

# Find packages from vcpkg
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

message(STATUS "Found fmt: ${fmt_VERSION}")
message(STATUS "Found spdlog: ${spdlog_VERSION}")
message(STATUS "Found nlohmann_json: ${nlohmann_json_VERSION}")

# Clang-Tidy integration (ONLY for library, not tests/benchmarks)
if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
    if(CLANG_TIDY_EXE)
        message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
        set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}")
    else()
        message(WARNING "clang-tidy requested but not found")
    endif()
endif()

# Cppcheck integration (ONLY for library, not tests/benchmarks)
if(ENABLE_CPPCHECK)
    find_program(CPPCHECK_EXE NAMES "cppcheck")
    if(CPPCHECK_EXE)
        message(STATUS "cppcheck found: ${CPPCHECK_EXE}")
        set(CPPCHECK_COMMAND
            "${CPPCHECK_EXE}"
            "--enable=all"
            "--inconclusive"
            "--force"
            "--inline-suppr"
            "--suppressions-list=${CMAKE_SOURCE_DIR}/.cppcheck-suppressions"
            "--error-exitcode=0"
        )
    else()
        message(WARNING "cppcheck requested but not found")
    endif()
endif()

# Library
add_library(mathlib 
    src/mathlib.cpp
    src/logger.cpp
)

target_include_directories(mathlib PUBLIC src)

# Link vcpkg dependencies
target_link_libraries(mathlib 
    PUBLIC 
        fmt::fmt
        spdlog::spdlog
        nlohmann_json::nlohmann_json
)

# Apply static analysis ONLY to library
if(ENABLE_CLANG_TIDY AND CLANG_TIDY_COMMAND)
    set_target_properties(mathlib PROPERTIES
        CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}"
    )
endif()

if(ENABLE_CPPCHECK AND CPPCHECK_COMMAND)
    set_target_properties(mathlib PROPERTIES
        CXX_CPPCHECK "${CPPCHECK_COMMAND}"
    )
endif()

# Add coverage flags if enabled
if(ENABLE_COVERAGE)
    message(STATUS "Code coverage enabled")
    
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(mathlib PUBLIC
            --coverage
            -O0
            -g
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
        
        target_compile_options(mathlib PUBLIC
            -fno-sanitize-recover=all
        )
    else()
        message(WARNING "Sanitizers requested but not supported by this compiler")
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

# Example executable to demonstrate vcpkg dependencies
add_executable(mathlib_example examples/example.cpp)
target_link_libraries(mathlib_example PRIVATE mathlib)