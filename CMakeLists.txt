cmake_minimum_required(VERSION 3.0.0)
project(VulkanTest VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++17 -O2")

file(GLOB_RECURSE sources ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(VulkanTest ${sources})

target_link_libraries(VulkanTest glfw vulkan dl pthread X11 Xxf86vm Xrandr Xi)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
