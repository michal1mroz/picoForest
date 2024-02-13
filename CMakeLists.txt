cmake_minimum_required(VERSION 3.26)
project(picoForest)
set(CMAKE_CXX_STANDARD 17)

# Can modify the version if you wish...
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

# set output to build/
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH  ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_executable(picoForest src/main.cpp)

target_link_libraries(picoForest GLEW glfw glm OpenGL)
