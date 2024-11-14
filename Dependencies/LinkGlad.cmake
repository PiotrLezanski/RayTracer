# Add glad source file
file(GLOB GLAD_SOURCE "Dependencies/glad/src/glad.c")

# Add glad source to the project
target_sources(${PROJECT_NAME} PRIVATE ${GLAD_SOURCE})

# Include glad directory for headers
target_include_directories(${PROJECT_NAME} PRIVATE "Dependencies/glad/include")