#!/bin/bash
# Script to publish documentation to GitHub Pages

set -e

echo "=========================================="
echo "Publishing Documentation to GitHub Pages"
echo "=========================================="

# Check if docs exist
if [ ! -d "docs/html" ]; then
    echo "Error: Documentation not found"
    echo "Please run: ./generate-docs.sh first"
    exit 1
fi

# Check if we're in a git repository
if ! git rev-parse --git-dir > /dev/null 2>&1; then
    echo "Error: Not in a git repository"
    exit 1
fi

# Get current branch
CURRENT_BRANCH=$(git rev-parse --abbrev-ref HEAD)
echo "Current branch: $CURRENT_BRANCH"

# Save current state
echo "Saving current state..."
git stash save "Stashing before docs deployment"

# Create or checkout gh-pages branch
if git rev-parse --verify gh-pages > /dev/null 2>&1; then
    echo "Checking out existing gh-pages branch..."
    git checkout gh-pages
else
    echo "Creating new gh-pages branch..."
    git checkout --orphan gh-pages
    git rm -rf .
fi

# Copy documentation
echo "Copying documentation..."
cp -r docs/html/* .

# Create .nojekyll file (tells GitHub Pages not to use Jekyll)
touch .nojekyll

# Add and commit
echo "Committing documentation..."
git add .
git commit -m "Update documentation (generated on $(date))" || echo "No changes to commit"

# Push to GitHub
echo "Pushing to GitHub..."
git push origin gh-pages --force

# Return to original branch
echo "Returning to $CURRENT_BRANCH..."
git checkout "$CURRENT_BRANCH"
git stash pop || true

echo ""
echo "=========================================="
echo "✅ Documentation published!"
echo "=========================================="
echo ""
echo "Documentation will be available at:"
echo "  https://yourusername.github.io/cpp-github-tutorial/"
echo ""
echo "(Replace 'yourusername' with your GitHub username)"
echo ""
echo "Note: It may take a few minutes for changes to appear"
echo "=========================================="