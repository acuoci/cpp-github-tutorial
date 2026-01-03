# Fetch Google Benchmark from GitHub
include(FetchContent)

FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG        v1.8.3
)

# Configure Google Benchmark
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Disable Google Benchmark tests" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "Disable Google Benchmark install" FORCE)

# Make Google Benchmark available
FetchContent_MakeAvailable(googlebenchmark)

# Create benchmark executable
add_executable(mathlib_benchmarks
    benchmark_mathlib.cpp
)

# Link with our library and Google Benchmark
target_link_libraries(mathlib_benchmarks PRIVATE
    mathlib
    benchmark::benchmark
)

# Set output directory (optional, for convenience)
set_target_properties(mathlib_benchmarks PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Optionally add as a CTest test (won't fail on performance regression, just runs)
add_test(NAME benchmarks 
         COMMAND mathlib_benchmarks --benchmark_min_time=0.1)