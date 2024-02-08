cmake_minimum_required(VERSION 3.26)
project(picoForest)

find_package(OpenGL REQUIRED)
find_package(X11 REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(picoForest src/main.cpp)

target_link_libraries(picoForest ${OPENGL_LIBRARIES} ${X11_LIBRARIES})

target_include_directories(picoForest PRIVATE ${OPENGL_INCLUDE_DIRS} ${X11_INCLUDE_DIR})
