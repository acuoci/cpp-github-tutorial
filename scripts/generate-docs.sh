#!/bin/bash
# Script to generate Doxygen documentation

set -e

echo "=========================================="
echo "Generating Documentation with Doxygen"
echo "=========================================="

# Check if doxygen is installed
if ! command -v doxygen &> /dev/null; then
    echo "Error: doxygen not found"
    echo "Please install it:"
    echo "  Ubuntu/Debian: sudo apt-get install doxygen graphviz"
    echo "  macOS: brew install doxygen graphviz"
    exit 1
fi

echo "Using Doxygen version:"
doxygen --version

# Check if dot (graphviz) is installed (for diagrams)
if command -v dot &> /dev/null; then
    echo "Graphviz found - will generate diagrams"
    dot -V
else
    echo "Warning: Graphviz (dot) not found - diagrams will not be generated"
    echo "Install with: sudo apt-get install graphviz (Linux) or brew install graphviz (macOS)"
fi

# Generate documentation
echo ""
echo "Generating documentation..."
doxygen Doxyfile

# Check if generation was successful
if [ -d "docs/html" ]; then
    echo ""
    echo "=========================================="
    echo "✅ Documentation generated successfully!"
    echo "=========================================="
    echo ""
    echo "Documentation location: docs/html/"
    echo ""
    echo "To view:"
    if [[ "$OSTYPE" == "darwin"* ]]; then
        echo "  open docs/html/index.html"
    elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
        echo "  xdg-open docs/html/index.html"
    else
        echo "  Open docs/html/index.html in your browser"
    fi
    echo ""
    echo "To publish to GitHub Pages:"
    echo "  1. Enable GitHub Pages in repository settings"
    echo "  2. Set source to 'gh-pages' branch"
    echo "  3. Push docs: ./publish-docs.sh"
    echo "=========================================="
else
    echo ""
    echo "❌ Error: Documentation generation failed"
    exit 1
fi