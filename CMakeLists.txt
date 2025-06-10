cmake_minimum_required(VERSION 3.10)
project(ParticleSimulator VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(particle_sim src/main.cpp)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(glad REQUIRED)

if (NOT glad_FOUND)
    message(FATAL_ERROR "glad not found")
endif()

if (NOT glm_FOUND)
    message(FATAL_ERROR "glm not found")
endif()

if (NOT glfw3_FOUND)
    message(FATAL_ERROR "glfw3 not found")
endif()

if (NOT OpenGL_FOUND)
    message(FATAL_ERROR "OpenGL not found")
endif()

target_link_libraries(particle_sim PRIVATE OpenGL::GL glfw glad glm::glm)

