cmake_minimum_required(VERSION 3.10)
project(SirSim)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
add_subdirectory(vendors/glfw/)

add_library(glad vendors/glad/src/glad.c)
target_include_directories(glad PRIVATE vendors/glad/include)

file(GLOB IMGUI_SOURCES vendors/imgui/*.cpp
    vendors/imgui/backends/imgui_impl_opengl3.cpp
    vendors/imgui/backends/imgui_impl_glfw.cpp
)
add_library(imgui ${IMGUI_SOURCES})
target_include_directories(imgui PRIVATE vendors/imgui/include
    vendors/imgui/backends/)
target_link_libraries(imgui PRIVATE glfw)
if (GLFW_BUILD_X11)
    find_package(X11)
    target_link_libraries(imgui PRIVATE ${X11_LIBRARIES})
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++20")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR}/
    vendors/glfw/include/
    vendors/imgui/
    vendors/glad/include/)

file(GLOB_RECURSE SIRSIM_CORE_SOURCES core/*.cpp)
file(GLOB_RECURSE SIRSIM_CORE_HEADERS core/*.h)
add_library(SirSimCore ${SIRSIM_CORE_SOURCES} ${SIRSIM_CORE_HEADERS})
target_link_libraries(SirSimCore PUBLIC imgui glfw glad)

target_precompile_headers(SirSimCore PUBLIC precompiled.h)

file(GLOB_RECURSE SIRSIM_APP_SOURCES sirsim/*.cpp)
file(GLOB_RECURSE SIRSIM_APP_HEADERS sirsim/*.h)
add_executable(SirSim ${SIRSIM_APP_SOURCES} ${SIRSIM_APP_HEADERS})
target_link_libraries(SirSim SirSimCore)
