#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>  // ADD THIS for take()
#include <catch2/generators/catch_generators_random.hpp>     // For random()
#include "mathlib.h"
#include <cmath>

using Catch::Approx;

// Test with sections (different scenarios in one test case)
TEST_CASE("Square function with various inputs", "[square][comprehensive]") {
    SECTION("Positive numbers") {
        REQUIRE(mathlib::square(1.0) == 1.0);
        REQUIRE(mathlib::square(10.0) == 100.0);
        REQUIRE(mathlib::square(100.0) == 10000.0);
    }
    
    SECTION("Negative numbers") {
        REQUIRE(mathlib::square(-1.0) == 1.0);
        REQUIRE(mathlib::square(-5.0) == 25.0);
        REQUIRE(mathlib::square(-10.0) == 100.0);
    }
    
    SECTION("Fractional numbers") {
        REQUIRE(mathlib::square(0.1) == Approx(0.01).epsilon(1e-10));
        REQUIRE(mathlib::square(0.5) == Approx(0.25).epsilon(1e-10));
        REQUIRE(mathlib::square(1.5) == Approx(2.25).epsilon(1e-10));
    }
    
    SECTION("Special values") {
        REQUIRE(mathlib::square(0.0) == 0.0);
        REQUIRE(std::isinf(mathlib::square(INFINITY)));
    }
}

// Parameterized test using generators
TEST_CASE("Factorial values are correct", "[factorial][parameterized]") {
    auto n = GENERATE(0, 1, 2, 3, 4, 5, 6, 7);
    
    // Expected factorial values
    double expected[] = {1.0, 1.0, 2.0, 6.0, 24.0, 120.0, 720.0, 5040.0};
    
    REQUIRE(mathlib::factorial(n) == expected[n]);
}

// Test mathematical properties
TEST_CASE("Square function mathematical properties", "[square][properties]") {
    SECTION("Symmetry: square(-x) == square(x)") {
        auto x = GENERATE(take(10, random(-100.0, 100.0)));
        REQUIRE(mathlib::square(-x) == Approx(mathlib::square(x)));
    }
    
    SECTION("Multiplication property: square(x) == x * x") {
        auto x = GENERATE(take(10, random(-100.0, 100.0)));
        REQUIRE(mathlib::square(x) == Approx(x * x));
    }
}

// Test edge cases
TEST_CASE("Edge cases and boundary conditions", "[edge_cases]") {
    SECTION("Very small numbers") {
        double tiny = 1e-100;
        REQUIRE(mathlib::square(tiny) == Approx(tiny * tiny).epsilon(1e-10));
    }
    
    SECTION("Very large numbers") {
        double large = 1e10;
        REQUIRE(mathlib::square(large) == Approx(large * large).epsilon(1e-5));
    }
    
    SECTION("Factorial boundary") {
        REQUIRE(mathlib::factorial(0) == 1.0);
        REQUIRE(mathlib::factorial(1) == 1.0);
    }
}

// Performance test (basic example)
TEST_CASE("Factorial performance is reasonable", "[factorial][performance]") {
    // This is a simple example - for real performance testing,
    // you'd use Catch2's benchmarking features
    for (int i = 0; i < 1000; ++i) {
        volatile double result = mathlib::factorial(10);
        (void)result; // Prevent optimization
    }
    SUCCEED("Performance test completed");
}

// Test with custom tags for organization
TEST_CASE("Square of integers", "[square][integers]") {
    REQUIRE(mathlib::square(2.0) == 4.0);
    REQUIRE(mathlib::square(3.0) == 9.0);
    REQUIRE(mathlib::square(4.0) == 16.0);
}