FetchContent_Declare(
	glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG b35641f4a3c62aa86a0b3c983d163bc0fe36026d
)

# Set options to disable unnecessary components
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# Fetch GLFW and make it available
FetchContent_MakeAvailable(glfw)