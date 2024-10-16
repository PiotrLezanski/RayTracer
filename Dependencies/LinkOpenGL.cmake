# Find the OpenGL package using the built-in CMake module
find_package(OpenGL REQUIRED)

# Check if OpenGL was found
if (OpenGL_FOUND)
    message(STATUS "Found OpenGL: ${OpenGL_LIBRARIES}")
else()
    message(FATAL_ERROR "OpenGL not found!")
endif()