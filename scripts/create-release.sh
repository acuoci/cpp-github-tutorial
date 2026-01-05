#!/bin/bash
# Script to create a new release

set -e

echo "=========================================="
echo "MathLib Release Tool"
echo "=========================================="

# Check if git repo
if ! git rev-parse --git-dir > /dev/null 2>&1; then
    echo "Error: Not in a git repository"
    exit 1
fi

# Check for uncommitted changes
if ! git diff-index --quiet HEAD --; then
    echo "Error: You have uncommitted changes"
    echo "Please commit or stash them first"
    exit 1
fi

# Get current version from git tags
CURRENT_TAG=$(git describe --tags --abbrev=0 2>/dev/null || echo "v0.0.0")
CURRENT_VERSION=${CURRENT_TAG#v}
echo "Current version: $CURRENT_VERSION"

# Parse current version
IFS='.' read -r MAJOR MINOR PATCH <<< "$CURRENT_VERSION"

# Ask for release type
echo ""
echo "Select release type:"
echo "  1) Patch ($MAJOR.$MINOR.$((PATCH + 1))) - Bug fixes"
echo "  2) Minor ($MAJOR.$((MINOR + 1)).0) - New features (backward compatible)"
echo "  3) Major ($((MAJOR + 1)).0.0) - Breaking changes"
echo "  4) Custom version"
echo ""
read -p "Choice (1-4): " CHOICE

case $CHOICE in
    1)
        PATCH=$((PATCH + 1))
        RELEASE_TYPE="patch"
        ;;
    2)
        MINOR=$((MINOR + 1))
        PATCH=0
        RELEASE_TYPE="minor"
        ;;
    3)
        MAJOR=$((MAJOR + 1))
        MINOR=0
        PATCH=0
        RELEASE_TYPE="major"
        ;;
    4)
        read -p "Enter version (e.g., 1.2.3): " CUSTOM_VERSION
        IFS='.' read -r MAJOR MINOR PATCH <<< "$CUSTOM_VERSION"
        RELEASE_TYPE="custom"
        ;;
    *)
        echo "Invalid choice"
        exit 1
        ;;
esac

NEW_VERSION="$MAJOR.$MINOR.$PATCH"
NEW_TAG="v$NEW_VERSION"

echo ""
echo "New version will be: $NEW_VERSION"
read -p "Continue? (y/n) " -n 1 -r
echo
if [[ ! $REPLY =~ ^[Yy]$ ]]; then
    echo "Cancelled"
    exit 1
fi

# Update version in CMakeLists.txt
echo ""
echo "Updating CMakeLists.txt..."
sed -i.bak "s/VERSION [0-9]\+\.[0-9]\+\.[0-9]\+/VERSION $NEW_VERSION/" CMakeLists.txt
rm -f CMakeLists.txt.bak

# Update version in Doxyfile if it exists
if [ -f "Doxyfile" ]; then
    echo "Updating Doxyfile..."
    sed -i.bak "s/PROJECT_NUMBER.*=.*/PROJECT_NUMBER         = $NEW_VERSION/" Doxyfile
    rm -f Doxyfile.bak
fi

# Generate changelog
echo ""
echo "Generating changelog..."
{
    echo "# Release $NEW_TAG"
    echo ""
    echo "Released on $(date +%Y-%m-%d)"
    echo ""
    echo "## Changes since $CURRENT_TAG"
    echo ""
    git log ${CURRENT_TAG}..HEAD --oneline --no-merges | sed 's/^/- /'
    echo ""
} > RELEASE_NOTES.md

echo "Release notes:"
cat RELEASE_NOTES.md

# Commit version changes
echo ""
echo "Committing version bump..."
git add CMakeLists.txt Doxyfile 2>/dev/null || git add CMakeLists.txt
git commit -m "chore: bump version to $NEW_VERSION"

# Create tag
echo "Creating tag $NEW_TAG..."
git tag -a "$NEW_TAG" -m "Release $NEW_TAG"

echo ""
echo "=========================================="
echo "✅ Release $NEW_TAG prepared!"
echo "=========================================="
echo ""
echo "Next steps:"
echo "  1. Review the changes:"
echo "     git log -1"
echo "     git show $NEW_TAG"
echo ""
echo "  2. Push to trigger release:"
echo "     git push origin main"
echo "     git push origin $NEW_TAG"
echo ""
echo "  3. GitHub Actions will:"
echo "     - Build binaries for all platforms"
echo "     - Create GitHub release with artifacts"
echo "     - Generate changelog"
echo "=========================================="