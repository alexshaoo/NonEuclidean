#!/bin/bash

# Build script for NonEuclidean (macOS/Linux)

echo "Building NonEuclidean..."

# Create build directory if it doesn't exist
if [ ! -d "build" ]; then
    echo "Creating build directory..."
    mkdir build
fi

# Navigate to build directory
cd build

# Clear CMake cache to avoid stale configuration
echo "Clearing CMake cache..."
rm -f CMakeCache.txt
rm -rf CMakeFiles

# Run CMake
# If CMake can't find SFML automatically, you can help it by setting:
#   -DSFML_DIR=/path/to/SFMLConfig.cmake directory
#   or -DCMAKE_PREFIX_PATH=/usr/local (or wherever SFML is installed)
echo "Running CMake..."
cmake ..

# Build the project
echo "Compiling..."
cmake --build .

# Check if build was successful
if [ $? -eq 0 ]; then
    echo ""
    echo "Build successful!"
    echo "Run the game with: ./build/NonEuclidean"
else
    echo ""
    echo "Build failed. Please check the error messages above."
    exit 1
fi
