/**
 * @file mathlib.cpp
 * @brief Implementation of mathematical library functions
 */

#include "mathlib.h"

#include <stdexcept>

namespace mathlib {

/**
 * @brief Implementation of square function
 *
 * Simple multiplication: x * x
 *
 * @details
 * This implementation uses direct multiplication rather than pow(x, 2)
 * for efficiency. Direct multiplication is:
 * - Faster (no function call overhead)
 * - More accurate (no floating-point exponentiation)
 * - Compiler can optimize effectively
 */
double square(double x) {
    return x * x;
}

/**
 * @brief Implementation of factorial function
 *
 * Iterative computation from 1 to n
 *
 * @details
 * Uses iterative approach instead of recursive for:
 * - Better performance (no stack overhead)
 * - No stack overflow risk for large n
 * - Easier to optimize by compiler
 *
 * Algorithm:
 * 1. Check for negative input (throw exception)
 * 2. Handle base cases (0! = 1, 1! = 1)
 * 3. Multiply from 2 to n iteratively
 *
 * @par Time Complexity:
 * O(n) where n is the input value
 *
 * @par Space Complexity:
 * O(1) - uses only constant extra space
 */
double factorial(int n) {
    // Input validation
    if (n < 0) {
        throw std::invalid_argument("Factorial of negative number is undefined");
    }

    // Base cases
    if (n == 0 || n == 1) {
        return 1.0;
    }

    // Iterative computation
    double result = 1.0;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }

    return result;
}

}  // namespace mathlib