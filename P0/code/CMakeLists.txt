cmake_minimum_required(VERSION 3.5)

# Project Name
PROJECT(class1)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_executable(${PROJECT_NAME} main.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

if(NOT OPENGL_FOUND)
    message(FATAL_ERROR "OpenGL not found!")
endif()

if(NOT GLUT_FOUND)
    message(FATAL_ERROR "GLUT not found!")
endif()

include_directories(${OpenGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS} ${GLUT_LIBRARY_DIRS})

message(STATUS "OpenGL Libraries: ${OPENGL_LIBRARIES}")
message(STATUS "GLUT Libraries: ${GLUT_LIBRARIES}")

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} GL GLU glut)







