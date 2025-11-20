cmake_minimum_required(VERSION 3.16)
project(NonEuclidean VERSION 1.1 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML (supports both 2.5+ and 3.x)
# SFML 3.x uses capitalized component names (Graphics, Window, System)
# SFML 2.x uses lowercase (graphics, window, system)

# Try to find SFML 3.x first, then fall back to any version
find_package(SFML 3 QUIET COMPONENTS Graphics Window System)

if(NOT SFML_FOUND)
    # Try finding any SFML version with capitalized components
    find_package(SFML QUIET COMPONENTS Graphics Window System)
endif()

if(NOT SFML_FOUND)
    # Try lowercase components for SFML 2.x
    find_package(SFML 2.5 QUIET COMPONENTS graphics window system)
endif()

if(NOT SFML_FOUND)
    # Last resort: try pkg-config (common on Linux)
    find_package(PkgConfig QUIET)
    if(PKG_CONFIG_FOUND)
        pkg_check_modules(SFML QUIET sfml-all>=2.5)
        if(NOT SFML_FOUND)
            # Try individual components
            pkg_check_modules(SFML_GRAPHICS REQUIRED sfml-graphics>=2.5)
            pkg_check_modules(SFML_WINDOW REQUIRED sfml-window>=2.5)
            pkg_check_modules(SFML_SYSTEM REQUIRED sfml-system>=2.5)

            set(SFML_LIBRARIES ${SFML_GRAPHICS_LIBRARIES} ${SFML_WINDOW_LIBRARIES} ${SFML_SYSTEM_LIBRARIES})
            set(SFML_INCLUDE_DIRS ${SFML_GRAPHICS_INCLUDE_DIRS})
            include_directories(${SFML_INCLUDE_DIRS})
            link_directories(${SFML_GRAPHICS_LIBRARY_DIRS})
            message(STATUS "Found SFML via pkg-config")
        else()
            set(SFML_LIBRARIES ${SFML_LIBRARIES})
            include_directories(${SFML_INCLUDE_DIRS})
            link_directories(${SFML_LIBRARY_DIRS})
            message(STATUS "Found SFML via pkg-config (sfml-all)")
        endif()
    else()
        message(FATAL_ERROR "SFML not found. Please install SFML 2.5+ or 3.x")
    endif()
else()
    # SFML found via CMake
    if(SFML_VERSION VERSION_GREATER_EQUAL "3.0.0")
        set(SFML_LIBRARIES SFML::Graphics SFML::Window SFML::System)
        message(STATUS "Found SFML ${SFML_VERSION} (using 3.x targets)")
    else()
        set(SFML_LIBRARIES sfml-graphics sfml-window sfml-system)
        message(STATUS "Found SFML ${SFML_VERSION} (using 2.x targets)")
    endif()
endif()

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

# Link SFML libraries (SFML_LIBRARIES was set during find_package)
target_link_libraries(NonEuclidean PRIVATE ${SFML_LIBRARIES})

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
