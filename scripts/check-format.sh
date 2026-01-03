#!/bin/bash
# Script to check if C++ code is properly formatted
# Returns exit code 1 if any files need formatting

set -e

echo "=========================================="
echo "Checking C++ Code Formatting"
echo "=========================================="

# Check if clang-format is installed
if ! command -v clang-format &> /dev/null; then
    echo "Error: clang-format not found"
    exit 1
fi

echo "Using clang-format version:"
clang-format --version

# Directories to check
DIRS_TO_CHECK="src tests benchmarks"

# Find all C++ files and check formatting
NEEDS_FORMATTING=()

echo ""
echo "Checking files in: $DIRS_TO_CHECK"
echo ""

for dir in $DIRS_TO_CHECK; do
    if [ -d "$dir" ]; then
        while IFS= read -r -d '' file; do
            # Check if file needs formatting
            if ! clang-format --dry-run --Werror "$file" 2>/dev/null; then
                NEEDS_FORMATTING+=("$file")
            fi
        done < <(find "$dir" -type f \( -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \) -print0)
    fi
done

# Report results
if [ ${#NEEDS_FORMATTING[@]} -eq 0 ]; then
    echo "=========================================="
    echo "✅ All files are properly formatted!"
    echo "=========================================="
    exit 0
else
    echo "=========================================="
    echo "❌ The following files need formatting:"
    echo "=========================================="
    for file in "${NEEDS_FORMATTING[@]}"; do
        echo "  - $file"
    done
    echo ""
    echo "To fix, run: ./format-code.sh"
    echo "Or: clang-format -i <filename>"
    echo "=========================================="
    exit 1
fi