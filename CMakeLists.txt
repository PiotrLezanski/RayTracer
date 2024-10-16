cmake_minimum_required (VERSION 3.8)

project(RayTracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include the dependencies CMake file
include(${CMAKE_SOURCE_DIR}/Dependencies/LinkDependencies.cmake)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

# Set architecture-specific output directories based on build configuration
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>)

# Add the executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Link dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE glfw OpenGL::GL)