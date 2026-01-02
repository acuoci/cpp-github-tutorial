#include <benchmark/benchmark.h>
#include "mathlib.h"
#include <vector>
#include <random>
#include <cmath>

//==============================================================================
// BASIC FUNCTION BENCHMARKS
// These test individual functions in isolation
//==============================================================================

static void BM_Square_Single(benchmark::State& state) {
    double x = 3.14159265358979323846;
    for (auto _ : state) {
        // DoNotOptimize prevents compiler from optimizing away the call
        benchmark::DoNotOptimize(mathlib::square(x));
        // ClobberMemory prevents reordering
        benchmark::ClobberMemory();
    }
    // This will show nanoseconds per call
}
BENCHMARK(BM_Square_Single);

static void BM_Factorial_Single(benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(mathlib::factorial(10));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_Factorial_Single);

//==============================================================================
// PARAMETERIZED BENCHMARKS
// Test how performance scales with input size
//==============================================================================

static void BM_Factorial_Parameterized(benchmark::State& state) {
    int n = state.range(0);
    for (auto _ : state) {
        benchmark::DoNotOptimize(mathlib::factorial(n));
    }
}
// Test with n = 5, 10, 15, 20
BENCHMARK(BM_Factorial_Parameterized)
    ->Arg(5)
    ->Arg(10)
    ->Arg(15)
    ->Arg(20);

//==============================================================================
// VECTOR OPERATIONS
// Simulate array/vector operations common in scientific computing
//==============================================================================

static void BM_Square_Vector(benchmark::State& state) {
    size_t n = state.range(0);
    
    // Setup: Create input and output vectors
    std::vector<double> input(n);
    std::vector<double> output(n);
    
    // Initialize with some data
    std::mt19937 gen(42);  // Fixed seed for reproducibility
    std::uniform_real_distribution<> dis(-100.0, 100.0);
    for (size_t i = 0; i < n; ++i) {
        input[i] = dis(gen);
    }
    
    // Benchmark: Square all elements
    for (auto _ : state) {
        for (size_t i = 0; i < n; ++i) {
            output[i] = mathlib::square(input[i]);
        }
        // Prevent optimization
        benchmark::DoNotOptimize(output.data());
        benchmark::ClobberMemory();
    }
    
    // Report how many items we processed
    state.SetItemsProcessed(state.iterations() * n);
    // Report bytes processed (useful for memory-bound operations)
    state.SetBytesProcessed(state.iterations() * n * sizeof(double) * 2);
}
BENCHMARK(BM_Square_Vector)
    ->Range(1<<10, 1<<20)      // 1K to 1M elements
    ->Unit(benchmark::kMicrosecond);

//==============================================================================
// MEMORY ACCESS PATTERNS
// Important for cache performance in HPC applications
//==============================================================================

static void BM_Square_Contiguous(benchmark::State& state) {
    size_t n = state.range(0);
    std::vector<double> data(n);
    
    // Initialize
    for (size_t i = 0; i < n; ++i) {
        data[i] = static_cast<double>(i);
    }
    
    // Benchmark: Contiguous memory access (cache-friendly)
    for (auto _ : state) {
        double sum = 0.0;
        for (size_t i = 0; i < n; ++i) {
            sum += mathlib::square(data[i]);
        }
        benchmark::DoNotOptimize(sum);
    }
    
    state.SetItemsProcessed(state.iterations() * n);
}
BENCHMARK(BM_Square_Contiguous)
    ->Range(1<<10, 1<<20);

static void BM_Square_Strided(benchmark::State& state) {
    size_t n = state.range(0);
    size_t stride = 16;  // Access every 16th element
    std::vector<double> data(n * stride);
    
    // Initialize
    for (size_t i = 0; i < n; ++i) {
        data[i * stride] = static_cast<double>(i);
    }
    
    // Benchmark: Strided memory access (cache-unfriendly)
    for (auto _ : state) {
        double sum = 0.0;
        for (size_t i = 0; i < n; ++i) {
            sum += mathlib::square(data[i * stride]);
        }
        benchmark::DoNotOptimize(sum);
    }
    
    state.SetItemsProcessed(state.iterations() * n);
}
BENCHMARK(BM_Square_Strided)
    ->Range(1<<10, 1<<20);

//==============================================================================
// COMPUTATIONAL COMPLEXITY ANALYSIS
// Verify algorithmic complexity (important for scalability)
//==============================================================================

static void BM_Factorial_Complexity(benchmark::State& state) {
    int n = state.range(0);
    for (auto _ : state) {
        benchmark::DoNotOptimize(mathlib::factorial(n));
    }
    state.SetComplexityN(n);
}
BENCHMARK(BM_Factorial_Complexity)
    ->RangeMultiplier(2)
    ->Range(1, 20)
    ->Complexity(benchmark::oN);  // Expected O(n) complexity

//==============================================================================
// REALISTIC WORKLOAD SIMULATION
// Mix of operations simulating real scientific computation
//==============================================================================

static void BM_MixedOperations(benchmark::State& state) {
    size_t n = state.range(0);
    std::vector<double> temperatures(n);
    std::vector<double> pressures(n);
    std::vector<double> results(n);
    
    // Initialize with realistic data
    std::mt19937 gen(42);
    std::uniform_real_distribution<> temp_dist(300.0, 2000.0);  // Kelvin
    std::uniform_real_distribution<> pres_dist(1e5, 10e5);      // Pascal
    
    for (size_t i = 0; i < n; ++i) {
        temperatures[i] = temp_dist(gen);
        pressures[i] = pres_dist(gen);
    }
    
    // Benchmark: Simulate some computation
    for (auto _ : state) {
        for (size_t i = 0; i < n; ++i) {
            // Example: some property calculation
            double T2 = mathlib::square(temperatures[i]);
            double P2 = mathlib::square(pressures[i]);
            results[i] = T2 / P2;  // Simplified
        }
        benchmark::DoNotOptimize(results.data());
        benchmark::ClobberMemory();
    }
    
    state.SetItemsProcessed(state.iterations() * n);
}
BENCHMARK(BM_MixedOperations)
    ->Range(1<<8, 1<<18)
    ->Unit(benchmark::kMicrosecond);

//==============================================================================
// WARMUP AND STABILITY TEST
// Ensure consistent measurements
//==============================================================================

static void BM_Square_WithWarmup(benchmark::State& state) {
    double x = 2.718281828;
    
    for (auto _ : state) {
        benchmark::DoNotOptimize(mathlib::square(x));
    }
}
BENCHMARK(BM_Square_WithWarmup)
    ->MinWarmUpTime(0.5);  // Warm up for 0.5 seconds

//==============================================================================
// COMPARISON: Different approaches
// Useful for testing optimization ideas
//==============================================================================

static void BM_Square_Direct(benchmark::State& state) {
    std::vector<double> data(1000);
    for (size_t i = 0; i < 1000; ++i) data[i] = static_cast<double>(i);
    
    for (auto _ : state) {
        for (auto& x : data) {
            x = mathlib::square(x);
        }
        benchmark::DoNotOptimize(data.data());
    }
}
BENCHMARK(BM_Square_Direct);

static void BM_Square_Manual(benchmark::State& state) {
    std::vector<double> data(1000);
    for (size_t i = 0; i < 1000; ++i) data[i] = static_cast<double>(i);
    
    for (auto _ : state) {
        for (auto& x : data) {
            x = x * x;  // Manual multiplication
        }
        benchmark::DoNotOptimize(data.data());
    }
}
BENCHMARK(BM_Square_Manual);

//==============================================================================
// MAIN
//==============================================================================

BENCHMARK_MAIN();