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

# Run CMake with SFML_DIR explicitly set
echo "Running CMake..."
cmake -DSFML_DIR=/usr/lib/cmake/SFML ..

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
