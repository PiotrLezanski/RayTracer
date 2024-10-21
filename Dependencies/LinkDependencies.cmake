include(FetchContent)
Set(FETCHCONTENT_QUIET FALSE)

include(${CMAKE_SOURCE_DIR}/Dependencies/LinkGLFW.cmake)
include(${CMAKE_SOURCE_DIR}/Dependencies/LinkOpenGL.cmake)
include(${CMAKE_SOURCE_DIR}/dependencies/LinkImGui.cmake)