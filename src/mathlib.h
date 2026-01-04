/**
 * @file mathlib.h
 * @brief Mathematical library providing basic mathematical operations
 *
 * This library provides fundamental mathematical functions including
 * power operations and factorial calculations, suitable for scientific
 * computing applications.
 *
 * @author Your Name
 * @date 2026-01-05
 * @version 1.0.0
 */

#ifndef MATHLIB_H
#define MATHLIB_H

/**
 * @namespace mathlib
 * @brief Mathematical operations namespace
 *
 * Contains mathematical functions for scientific computing.
 */
namespace mathlib {

/**
 * @brief Computes the square of a number
 *
 * Calculates \f$ x^2 \f$ for a given input value.
 *
 * This function is commonly used in:
 * - Distance calculations: \f$ d = \sqrt{x^2 + y^2} \f$
 * - Energy computations: \f$ E = \frac{1}{2}mv^2 \f$
 * - Statistical variance calculations
 *
 * @param x The input value
 * @return The square of x (x²)
 *
 * @par Example:
 * @code
 * double value = 5.0;
 * double result = mathlib::square(value);  // result = 25.0
 * @endcode
 *
 * @par Complexity:
 * O(1) - Constant time operation
 *
 * @note This function is numerically stable for all finite double values
 * @warning For very large values, result may overflow to infinity
 *
 * @see factorial()
 */
double square(double x);

/**
 * @brief Computes the factorial of a non-negative integer
 *
 * Calculates \f$ n! = n \times (n-1) \times (n-2) \times \ldots \times 1 \f$
 *
 * The factorial function is defined as:
 * \f[
 *   n! = \begin{cases}
 *          1 & \text{if } n = 0 \\
 *          n \times (n-1)! & \text{if } n > 0
 *        \end{cases}
 * \f]
 *
 * Common applications:
 * - Combinatorics: \f$ \binom{n}{k} = \frac{n!}{k!(n-k)!} \f$
 * - Probability distributions (Poisson, etc.)
 * - Taylor series expansions: \f$ e^x = \sum_{n=0}^{\infty} \frac{x^n}{n!} \f$
 *
 * @param n The input non-negative integer
 * @return The factorial of n (n!)
 *
 * @throw std::invalid_argument if n < 0
 *
 * @par Example:
 * @code
 * double result = mathlib::factorial(5);  // result = 120.0
 *
 * // For binomial coefficient:
 * int n = 10, k = 3;
 * double binom = factorial(n) / (factorial(k) * factorial(n - k));
 * @endcode
 *
 * @par Complexity:
 * O(n) - Linear time in the value of n
 *
 * @par Numerical Limits:
 * - Maximum accurately representable: n ≤ 170
 * - For n > 170, result overflows to infinity
 * - Consider using logarithmic factorial for large n
 *
 * @note Returns exact results up to n = 20
 * @warning For n > 170, overflow occurs (returns infinity)
 * @warning Computational cost grows linearly with n
 *
 * @see square()
 *
 * @par Implementation Notes:
 * Uses iterative computation for efficiency. For applications requiring
 * factorial of large numbers, consider Stirling's approximation:
 * \f$ \ln(n!) \approx n\ln(n) - n + \frac{1}{2}\ln(2\pi n) \f$
 */
double factorial(int n);

}  // namespace mathlib

#endif  // MATHLIB_H