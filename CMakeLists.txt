cmake_minimum_required(VERSION 3.14.0)
project(vulkan VERSION 0.1.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++17 -O2")

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_definitions(-DPROJECT_NAME="${PROJECT_NAME}")
add_definitions(-DPROJECT_VERSION="${PROJECT_VERSION}")
add_executable(${PROJECT_NAME} ${SOURCES})

if (WIN32)
    target_include_directories(${PROJECT_NAME} PUBLIC
        "C:\\TDM-GCC-64\\x86_64-w64-mingw32\\include"
        "C:\\VulkanSDK\\1.2.182.0\\Include"
        "C:\\SDKs\\glfw\\include"
        "C:\\SDKs\\glm\\"
        "C:\\SDKs\\spdlog\\include"
    )

    target_link_directories(${PROJECT_NAME} PUBLIC
        "C:\\TDM-GCC-64\\x86_64-w64-mingw32\\lib"
        "C:\\VulkanSDK\\1.2.182.0\\Lib"
        "C:\\SDKs\\glfw\\lib-mingw-w64"
    )

    target_link_libraries(${PROJECT_NAME} glfw3 vulkan-1)
elseif (UNIX)
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${VULKAN_SDK}/include"
    )

    target_link_directories(${PROJECT_NAME} PUBLIC
        "${VULKAN_SDK}/lib"
    )

    target_link_libraries(${PROJECT_NAME} glfw vulkan)
endif()


