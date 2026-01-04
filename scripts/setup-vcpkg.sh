#!/bin/bash
# Script to install and setup vcpkg

set -e

echo "=========================================="
echo "Setting up vcpkg"
echo "=========================================="

VCPKG_DIR="$HOME/vcpkg"

# Check if vcpkg is already installed
if [ -d "$VCPKG_DIR" ]; then
    echo "vcpkg already installed at $VCPKG_DIR"
    echo "Updating vcpkg..."
    cd "$VCPKG_DIR"
    git pull
else
    echo "Installing vcpkg to $VCPKG_DIR..."
    git clone https://github.com/microsoft/vcpkg.git "$VCPKG_DIR"
    cd "$VCPKG_DIR"
fi

# Bootstrap vcpkg
echo ""
echo "Bootstrapping vcpkg..."
if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "win32" ]]; then
    ./bootstrap-vcpkg.bat
else
    ./bootstrap-vcpkg.sh
fi

# Set environment variable
echo ""
echo "=========================================="
echo "✅ vcpkg installed successfully!"
echo "=========================================="
echo ""
echo "To use vcpkg, add this to your shell profile (~/.bashrc, ~/.zshrc, etc.):"
echo ""
echo "  export VCPKG_ROOT=\"$VCPKG_DIR\""
echo ""
echo "Or run this command now:"
echo "  export VCPKG_ROOT=\"$VCPKG_DIR\""
echo ""
echo "Then configure your project:"
echo "  cmake -B build -DCMAKE_TOOLCHAIN_FILE=\$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"
echo "=========================================="

# Offer to add to shell profile
read -p "Add VCPKG_ROOT to ~/.bashrc? (y/n) " -n 1 -r
echo
if [[ $REPLY =~ ^[Yy]$ ]]; then
    if ! grep -q "VCPKG_ROOT" ~/.bashrc; then
        echo "" >> ~/.bashrc
        echo "# vcpkg" >> ~/.bashrc
        echo "export VCPKG_ROOT=\"$VCPKG_DIR\"" >> ~/.bashrc
        echo "✅ Added to ~/.bashrc"
        echo "Run: source ~/.bashrc"
    else
        echo "VCPKG_ROOT already in ~/.bashrc"
    fi
fi