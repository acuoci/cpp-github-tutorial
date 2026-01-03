#!/bin/bash
# Script to generate code coverage reports
# Usage: ./generate_coverage.sh

set -e  # Exit on error

BUILD_DIR="build"
COVERAGE_INFO="coverage.info"
COVERAGE_FILTERED="coverage_filtered.info"
COVERAGE_HTML="coverage_html"

echo "=========================================="
echo "Generating Code Coverage Report"
echo "=========================================="

# Check if build directory exists
if [ ! -d "$BUILD_DIR" ]; then
    echo "Error: Build directory '$BUILD_DIR' not found"
    echo "Please run: cmake -B build -DENABLE_COVERAGE=ON && cmake --build build"
    exit 1
fi

# Check if tests were run
GCDA_COUNT=$(find "$BUILD_DIR" -name "*.gcda" | wc -l)
if [ "$GCDA_COUNT" -eq 0 ]; then
    echo "Error: No .gcda files found. Did you run the tests?"
    echo "Please run: ctest --test-dir build"
    exit 1
fi

echo "Found $GCDA_COUNT .gcda files"

# Capture coverage data (with error handling)
echo ""
echo "Capturing coverage data..."
lcov --capture \
     --directory "$BUILD_DIR" \
     --output-file "$COVERAGE_INFO" \
     --ignore-errors inconsistent,mismatch,gcov \
     --rc lcov_branch_coverage=1

# Remove unwanted coverage (system headers, tests, dependencies)
echo ""
echo "Filtering coverage data..."
lcov --remove "$COVERAGE_INFO" \
     '/usr/*' \
     '/opt/*' \
     '/Library/*' \
     '*/tests/*' \
     '*/test_*.cpp' \
     '*/build/_deps/*' \
     '*/.cache/*' \
     --output-file "$COVERAGE_FILTERED" \
     --ignore-errors unused \
     --rc lcov_branch_coverage=1

# Generate HTML report
echo ""
echo "Generating HTML report..."
genhtml "$COVERAGE_FILTERED" \
        --output-directory "$COVERAGE_HTML" \
        --branch-coverage \
        --title "MathLib Coverage Report" \
        --legend \
        --demangle-cpp

# Print summary
echo ""
echo "=========================================="
echo "Coverage Report Summary"
echo "=========================================="
lcov --summary "$COVERAGE_FILTERED" --rc lcov_branch_coverage=1

echo ""
echo "=========================================="
echo "HTML report generated at: $COVERAGE_HTML/index.html"
echo ""
echo "To view:"
if [[ "$OSTYPE" == "darwin"* ]]; then
    echo "  open $COVERAGE_HTML/index.html"
elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
    echo "  xdg-open $COVERAGE_HTML/index.html"
else
    echo "  Open $COVERAGE_HTML/index.html in your browser"
fi
echo "=========================================="