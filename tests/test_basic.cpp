#include <catch2/catch_test_macros.hpp>
#include "mathlib.h"

// Simple test cases
TEST_CASE("Square function works correctly", "[square]") {
    REQUIRE(mathlib::square(0.0) == 0.0);
    REQUIRE(mathlib::square(1.0) == 1.0);
    REQUIRE(mathlib::square(2.0) == 4.0);
    REQUIRE(mathlib::square(-3.0) == 9.0);
    REQUIRE(mathlib::square(0.5) == 0.25);
}

TEST_CASE("Factorial function works correctly", "[factorial]") {
    REQUIRE(mathlib::factorial(0) == 1.0);
    REQUIRE(mathlib::factorial(1) == 1.0);
    REQUIRE(mathlib::factorial(5) == 120.0);
    REQUIRE(mathlib::factorial(10) == 3628800.0);
}

TEST_CASE("Factorial of negative number throws exception", "[factorial][exceptions]") {
    REQUIRE_THROWS_AS(mathlib::factorial(-1), std::invalid_argument);
    REQUIRE_THROWS_AS(mathlib::factorial(-5), std::invalid_argument);
}