# Fetch Google Benchmark
include(FetchContent)

FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG        v1.8.3
)

# Don't build benchmark tests
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googlebenchmark)

# Create benchmark executable
add_executable(mathlib_benchmarks
    benchmark_mathlib.cpp
)

target_link_libraries(mathlib_benchmarks PRIVATE
    mathlib
    benchmark::benchmark
)

# Optional: Add as a test (will run but not fail on regression)
add_test(NAME benchmarks COMMAND mathlib_benchmarks)