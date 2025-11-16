cmake_minimum_required(VERSION 3.16)
project(NonEuclidean VERSION 1.1 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Source files
set(SOURCES
    NonEuclidean/main.cpp
    NonEuclidean/player.cpp
    NonEuclidean/render.cpp
    NonEuclidean/node.cpp
    NonEuclidean/texture.cpp
    NonEuclidean/textures.cpp
)

# Header files
set(HEADERS
    NonEuclidean/main.hpp
    NonEuclidean/player.hpp
    NonEuclidean/render.hpp
    NonEuclidean/node.hpp
    NonEuclidean/texture.hpp
    NonEuclidean/textures.hpp
)

# Create executable
add_executable(NonEuclidean ${SOURCES} ${HEADERS})

# Link SFML libraries
target_link_libraries(NonEuclidean PRIVATE sfml-graphics sfml-window sfml-system)

# Copy font file to build directory
configure_file(${CMAKE_SOURCE_DIR}/NonEuclidean/ubuntu.ttf ${CMAKE_BINARY_DIR}/ubuntu.ttf COPYONLY)

# Set output directory
set_target_properties(NonEuclidean PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Platform-specific settings
if(APPLE)
    # macOS specific settings
    set_target_properties(NonEuclidean PROPERTIES
        MACOSX_BUNDLE FALSE
    )
elseif(UNIX AND NOT APPLE)
    # Linux specific settings
    target_link_libraries(NonEuclidean PRIVATE pthread)
endif()

# Enable warnings
if(MSVC)
    target_compile_options(NonEuclidean PRIVATE /W4)
else()
    target_compile_options(NonEuclidean PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Print build info
message(STATUS "Building NonEuclidean v${PROJECT_VERSION}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
