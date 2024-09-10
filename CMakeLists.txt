# Mandatory line, sets the minimum version of CMake that should be used with this repository.
cmake_minimum_required(VERSION 3.22)

# Sets a few variables, like PROJECT_NAME
project(YouTube2Ableton)

# Always use the newest C++ standard on green-field projects if possible.
set(CMAKE_CXX_STANDARD 20)

# Download dependencies
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)

include(cmake/cpm.cmake)

CPMAddPackage(
    NAME JUCE
    GIT_TAG 8.0.1
    VERSION 8.0.1
    GITHUB_REPOSITORY juce-framework/JUCE
    SOURCE_DIR ${LIB_DIR}/juce
)

# Find Python interpreter, libraries, and header files
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

# Include Python headers
include_directories(${Python3_INCLUDE_DIRS})

# Add subdirectories
add_subdirectory(plugin)

# Link Python libraries to MyPlugin after the target is created
target_link_libraries(AudioPlugin PRIVATE Python3::Python)

# Set the path to custom CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Find FFmpeg
find_package(FFmpeg REQUIRED)

# Link FFmpeg libraries
target_link_libraries(AudioPlugin PRIVATE ${FFMPEG_LIBRARIES})

# Optionally pass the path to ffmpeg and ffprobe to your application
target_compile_definitions(AudioPlugin PRIVATE 
    FFMPEG_EXECUTABLE="${FFMPEG_EXECUTABLE}"
    FFPROBE_EXECUTABLE="${FFPROBE_EXECUTABLE}"
)
