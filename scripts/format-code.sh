#!/bin/bash
# Script to format all C++ code using clang-format

set -e

echo "=========================================="
echo "Formatting C++ Code"
echo "=========================================="

# Check if clang-format is installed
if ! command -v clang-format &> /dev/null; then
    echo "Error: clang-format not found"
    echo "Please install it:"
    echo "  Ubuntu/Debian: sudo apt-get install clang-format"
    echo "  macOS: brew install clang-format"
    exit 1
fi

echo "Using clang-format version:"
clang-format --version

# Directories to format
DIRS_TO_FORMAT="src tests benchmarks"

# Find and format all C++ files
echo ""
echo "Formatting files in: $DIRS_TO_FORMAT"
echo ""

for dir in $DIRS_TO_FORMAT; do
    if [ -d "$dir" ]; then
        echo "Processing $dir/..."
        find "$dir" -type f \( -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \) \
            -exec echo "  Formatting: {}" \; \
            -exec clang-format -i {} \;
    fi
done

echo ""
echo "=========================================="
echo "✅ Formatting complete!"
echo "=========================================="
echo ""
echo "Files have been formatted in-place."
echo "Review changes with: git diff"