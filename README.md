# MathLib - Mathematical Operations Library

[![CI](https://github.com/yourusername/cpp-github-tutorial/workflows/CI/badge.svg)](https://github.com/yourusername/cpp-github-tutorial/actions)
[![codecov](https://codecov.io/gh/yourusername/cpp-github-tutorial/branch/main/graph/badge.svg)](https://codecov.io/gh/yourusername/cpp-github-tutorial)
[![Documentation](https://img.shields.io/badge/docs-doxygen-blue.svg)](https://yourusername.github.io/cpp-github-tutorial/)

A professional C++ library providing fundamental mathematical operations, designed as a tutorial for modern C++ development practices.

## Features

- ✨ **Simple API** - Easy-to-use mathematical functions
- 🧪 **Well-tested** - Comprehensive test suite with Catch2
- 📊 **Benchmarked** - Performance regression detection
- 🔍 **Analyzed** - Static analysis with clang-tidy and cppcheck
- 📈 **Covered** - Code coverage tracking with Codecov
- 📚 **Documented** - Full API documentation with Doxygen
- 🚀 **Multi-platform** - Linux, macOS, and Windows support

## Quick Start

### Installation

```bash
git clone https://github.com/yourusername/cpp-github-tutorial.git
cd cpp-github-tutorial
mkdir build && cd build
cmake ..
make
```

### Usage

```cpp
#include "mathlib.h"
#include <iostream>

int main() {
    // Compute square
    double x = 5.0;
    double x_squared = mathlib::square(x);
    std::cout << x << "² = " << x_squared << std::endl;

    // Compute factorial
    int n = 10;
    double n_factorial = mathlib::factorial(n);
    std::cout << n << "! = " << n_factorial << std::endl;

    return 0;
}
```

Compile and link:

```bash
g++ -std=c++17 example.cpp -I./src -L./build -lmathlib -o example
./example
```

## API Reference

### Functions

#### `double mathlib::square(double x)`

Computes the square of a number: x²

**Parameters:**

- `x` - Input value

**Returns:** The square of x

**Example:**

```cpp
double result = mathlib::square(5.0);  // result = 25.0
```

**Mathematical Definition:**

f(x) = x²

---

#### `double mathlib::factorial(int n)`

Computes the factorial of a non-negative integer: n!

**Parameters:**

- `n` - Non-negative integer

**Returns:** The factorial of n

**Throws:** `std::invalid_argument` if n < 0

**Example:**

```cpp
double result = mathlib::factorial(5);  // result = 120.0
```

**Mathematical Definition:**

n! = n × (n-1) × (n-2) × ... × 1

for n ≥ 1, and 0! = 1

---

## Building from Source

### Requirements

- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.15 or higher

### Build Options

```bash
# Release build
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build

# Debug build with coverage
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DENABLE_COVERAGE=ON
cmake --build build

# With static analysis
cmake -B build -DENABLE_CLANG_TIDY=ON -DENABLE_CPPCHECK=ON
cmake --build build

# With sanitizers
cmake -B build -DENABLE_SANITIZERS=ON
cmake --build build
```

## Testing

Run tests with:

```bash
cd build
ctest --output-on-failure
```

Or run the test executable directly:

```bash
./build/tests/tests
```

### Test Options

```bash
# Run specific test cases
./build/tests/tests [square]
./build/tests/tests [factorial]

# Verbose output
./build/tests/tests --success

# List all tests
./build/tests/tests --list-tests
```

## Performance Benchmarking

Run benchmarks:

```bash
./build/bin/mathlib_benchmarks
```

Save results:

```bash
./build/bin/mathlib_benchmarks --benchmark_format=json --benchmark_out=results.json
```

## Documentation

### Building Documentation

Requires Doxygen (install with `sudo apt-get install doxygen graphviz` on Linux or `brew install doxygen graphviz` on macOS):

```bash
doxygen Doxyfile
```

Open documentation:

```bash
open docs/html/index.html  # macOS
xdg-open docs/html/index.html  # Linux
```

### Online Documentation

Visit the [online documentation](https://yourusername.github.io/cpp-github-tutorial/) for the latest API reference.

## Development

### Code Style

This project uses clang-format for consistent code formatting:

```bash
# Format all code
./format-code.sh

# Check formatting
./check-format.sh
```

### Static Analysis

Run static analysis tools:

```bash
# Clang-Tidy
cmake -B build -DENABLE_CLANG_TIDY=ON
cmake --build build

# Cppcheck
cmake -B build -DENABLE_CPPCHECK=ON
cmake --build build
```

### Code Coverage

Generate coverage report:

```bash
cmake -B build -DENABLE_COVERAGE=ON
cmake --build build
ctest --test-dir build
./generate_coverage.sh
```

## Contributing

Contributions are welcome! Please ensure:

1. ✅ All tests pass
2. ✅ Code is formatted (`./format-code.sh`)
3. ✅ No static analysis warnings
4. ✅ Code coverage maintained or improved
5. ✅ Documentation updated

## Project Structure

```
cpp-github-tutorial/
├── src/              # Source files
│   ├── mathlib.h
│   └── mathlib.cpp
├── tests/            # Test files
│   ├── test_main.cpp
│   ├── test_basic.cpp
│   └── test_mathlib.cpp
├── benchmarks/       # Performance benchmarks
│   └── benchmark_mathlib.cpp
├── docs/             # Generated documentation
├── .github/          # CI/CD workflows
│   └── workflows/
│       └── ci.yml
├── CMakeLists.txt    # Build configuration
├── Doxyfile          # Documentation configuration
├── .clang-format     # Code formatting rules
└── README.md         # This file
```

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- Built with [CMake](https://cmake.org/)
- Testing with [Catch2](https://github.com/catchorg/Catch2)
- Benchmarking with [Google Benchmark](https://github.com/google/benchmark)
- Documentation with [Doxygen](https://www.doxygen.nl/)

## Contact

- **Author**: Alberto Cuoci
- **Email**: alberto.cuoci@polimi.it
- **GitHub**: [@acuoci](https://github.com/acuoci)

---

**Note**: This project serves as a tutorial for modern C++ development practices including CI/CD, testing, benchmarking, static analysis, and documentation generation.
