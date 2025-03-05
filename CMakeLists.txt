cmake_minimum_required(VERSION 3.10)
project(CityLandscape)

set(CMAKE_CXX_STANDARD 11)

# Mac Silicon specific paths
if(APPLE)
    list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew/Cellar/glfw/3.4")
    list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew/Cellar/glm/1.0.1")
    include_directories("/opt/homebrew/include")
    link_directories("/opt/homebrew/lib")
endif()

# Find required packages
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories("/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/v1")


# Add source files
set(SOURCES 
    src/main.cpp
    src/glad.c
)

# Create executable
add_executable(city_landscape ${SOURCES})

# Link libraries
target_link_libraries(city_landscape glfw)

# Platform specific linking
if(UNIX AND NOT APPLE)
    target_link_libraries(city_landscape dl)
endif()

# For macOS, add OpenGL framework
if(APPLE)
    target_link_libraries(city_landscape "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreFoundation")
endif()