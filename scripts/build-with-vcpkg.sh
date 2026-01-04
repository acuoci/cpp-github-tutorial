#!/bin/bash
# Script to build project with vcpkg dependencies

set -e

echo "=========================================="
echo "Building MathLib with vcpkg"
echo "=========================================="

# Check if VCPKG_ROOT is set
if [ -z "$VCPKG_ROOT" ]; then
    echo "Error: VCPKG_ROOT environment variable not set"
    echo ""
    echo "Please set it to your vcpkg installation directory:"
    echo "  export VCPKG_ROOT=~/vcpkg"
    echo ""
    echo "Or run the setup script:"
    echo "  ./setup-vcpkg.sh"
    exit 1
fi

echo "Using vcpkg at: $VCPKG_ROOT"
echo ""

# Check if vcpkg executable exists
if [ ! -f "$VCPKG_ROOT/vcpkg" ]; then
    echo "Error: vcpkg executable not found at $VCPKG_ROOT/vcpkg"
    echo "Please run: ./setup-vcpkg.sh"
    exit 1
fi

# Clean previous build
if [ -d "build" ]; then
    echo "Cleaning previous build..."
    rm -rf build
fi

# Configure with CMake using vcpkg toolchain
echo "Configuring with CMake..."
cmake -B build \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" \
    -DUSE_VCPKG_DEPENDENCIES=ON \
    -DBUILD_BENCHMARKS=ON

echo ""
echo "Building..."
cmake --build build --config Release

echo ""
echo "=========================================="
echo "✅ Build successful!"
echo "=========================================="
echo ""
echo "Executables:"
echo "  Library: build/libmathlib.a"
echo "  Tests: build/tests/tests"
echo "  Benchmarks: build/bin/mathlib_benchmarks"
echo "  Example: build/mathlib_example"
echo ""
echo "To run the example:"
echo "  ./build/mathlib_example"
echo ""
echo "To run tests:"
echo "  ctest --test-dir build --output-on-failure"
echo "=========================================="