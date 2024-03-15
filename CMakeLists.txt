cmake_minimum_required(VERSION 3.0.0)
project(FluidSim VERSION 0.1.0 LANGUAGES C CXX)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)

include(CTest)
enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/inc)

add_executable(FluidSim 
    src/main.cpp 
    src/glad.c
    src/utils.cpp
    src/particle.cpp
)

target_link_libraries(FluidSim 
    glfw
    OpenGL::GL
    glm::glm
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
