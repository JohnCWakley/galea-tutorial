cmake_minimum_required(VERSION 3.14.0)
project(demo VERSION 0.1.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++17 -O2")

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_definitions(-DPROJECT_NAME="${PROJECT_NAME}")
add_definitions(-DPROJECT_VERSION="${PROJECT_VERSION}")

add_executable(${PROJECT_NAME} ${SOURCES})

if (WIN32)
    target_include_directories(${PROJECT_NAME} PUBLIC
        "D:\\TDM-GCC-64\\x86_64-w64-mingw32\\include"
        "D:\\sdks\\vulkan\\1.2.182.0\\Include"
        "D:\\sdks\\glfw\\include"
        "D:\\sdks\\glm"
        "D:\\sdks\\spdlog\\include"
        "D:\\sdks\\tiny_obj_loader"
    )

    target_link_directories(${PROJECT_NAME} PUBLIC
        "D:\\TDM-GCC-64\\x86_64-w64-mingw32\\lib"
        "D:\\sdks\\vulkan\\1.2.182.0\\Lib"
        "D:\\sdks\\glfw\\lib-mingw-w64"
    )

    target_link_libraries(${PROJECT_NAME} glfw3 vulkan-1)
elseif (UNIX)
    target_link_libraries(${PROJECT_NAME} glfw vulkan)
endif()


