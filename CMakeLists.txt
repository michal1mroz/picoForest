cmake_minimum_required(VERSION 3.26)
project(picoForest)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

# stop glfw tests, documentation and examples from
# compiling
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# set output to build/
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH  ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_executable(picoForest src/main.cpp)

add_subdirectory(lib/glfw-3.3.9)

# Got to link against OpenGL or it won't work :<
target_link_libraries(picoForest glfw OpenGL)
