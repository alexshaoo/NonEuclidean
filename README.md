# NonEuclidean

## Info
NonEuclidean is a 3D game engine that simulates non-euclidean geometries. Players can explore the world and solve puzzles using these unique geometric mechanics.

## Technologies
This project was built with:
* C++ (C++17 or later)
* SFML 2.5+ library for graphics and input handling
* CMake 3.16+ for cross-platform builds

## Setup

### Prerequisites
Install SFML 2.5 or later:

**macOS** (using Homebrew):
```bash
brew install sfml
```

**Ubuntu/Debian**:
```bash
sudo apt-get update
sudo apt-get install libsfml-dev
```

**Arch Linux**:
```bash
sudo pacman -S sfml
```

**Windows**:
- Download SFML from the [official website](https://www.sfml-dev.org/download.php)
- Or use Visual Studio with the included project files

### Building with CMake (macOS/Linux/Windows)

**Quick Build (macOS/Linux)**:
```bash
./build.sh
./build/NonEuclidean
```

**Manual Build**:

1. Clone this repository:
```bash
git clone https://github.com/yourusername/NonEuclidean.git
cd NonEuclidean
```

2. Create a build directory:
```bash
mkdir build
cd build
```

3. Generate build files and compile:
```bash
cmake ..
cmake --build .
```

4. Run the game:
```bash
./NonEuclidean
```

### Building with Visual Studio (Windows)

1. Clone this repository
2. Open `NonEuclidean/NonEuclidean.sln` in Visual Studio
3. Build and run the project (F5)

If you encounter any issues during setup, please refer to the Troubleshooting section below.

## Troubleshooting
If you encounter issues while setting up the project, try the following solutions:
* If the SFML installation is causing issues, follow the steps outlined in [this YouTube tutorial](https://www.youtube.com/watch?v=lFzpkvrscs4).

## v1.1
Added mouse control with basic options menu! Will try to render FOV and graphics quality dynamically dependent on settings.

## What now?
At the time of writing, I'm  on expanding the game mechanics and adding more levels to the game. Stay tuned for updates!
