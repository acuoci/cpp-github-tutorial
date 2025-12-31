#include "mathlib.h"
#include <iostream>
#include <cmath>

int main() {
    // Test square function
    if (std::abs(mathlib::square(5.0) - 25.0) > 1e-10) {
        std::cerr << "Test failed: square(5.0) != 25.0" << std::endl;
        return 1;
    }
    
    // Test factorial function
    if (std::abs(mathlib::factorial(5) - 120.0) > 1e-10) {
        std::cerr << "Test failed: factorial(5) != 120.0" << std::endl;
        return 1;
    }
    
    std::cout << "All tests passed!" << std::endl;
    return 0;
}