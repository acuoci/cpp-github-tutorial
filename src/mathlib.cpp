#include "mathlib.h"

#include <stdexcept>

// Implementation of the mathlib functions

namespace mathlib {
double square(double x) {
    return x * x;
}

double factorial(int n) {
    if (n < 0)
        throw std::invalid_argument("Factorial of negative number");
    if (n == 0 || n == 1)
        return 1.0;
    double result = 1.0;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}
}  // namespace mathlib
