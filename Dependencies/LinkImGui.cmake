FetchContent_Declare(      
    imgui                  
    GIT_REPOSITORY "https://github.com/ocornut/imgui"
    GIT_TAG v1.91.4
    GIT_PROGRESS TRUE
)
 
FetchContent_MakeAvailable(imgui)
 
# Set the ImGui directory
set(IMGUI_DIR ${imgui_SOURCE_DIR})

# Include ImGui source files (core and backends)
file(GLOB IMGUI_SOURCES
    ${IMGUI_DIR}/*.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)   

# Add ImGui sources to the project
target_sources(${PROJECT_NAME} PRIVATE ${IMGUI_SOURCES})

# Include directories for ImGui headers
target_include_directories(${PROJECT_NAME} PRIVATE ${IMGUI_DIR} ${IMGUI_DIR}/backends)