cmake_minimum_required(VERSION 3.20.0)
project(demo VERSION 0.1.0)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

if (WIN32)
    target_include_directories(${PROJECT_NAME} PUBLIC
        $ENV{MINGW_ROOT}/x86_64-w64-mingw32/include
        $ENV{USERPROFILE}/dev/sdks/vulkan/Include
        $ENV{USERPROFILE}/dev/sdks/glfw/include
        $ENV{USERPROFILE}/dev/sdks/glm/glm
        ${PROJECT_SOURCE_DIR}/src/third_party
    )

    target_link_directories(${PROJECT_NAME} PUBLIC
        $ENV{MINGW_ROOT}/x86_64-w64-mingw32/lib
        $ENV{USERPROFILE}/dev/sdks/vulkan/Lib
        $ENV{USERPROFILE}/dev/sdks/glfw/lib-mingw-w64
    )

    target_link_libraries(${PROJECT_NAME} glfw3 vulkan-1)
elseif (UNIX)
    target_include_directories(${PROJECT_NAME} PUBLIC src/third_party)
    target_link_libraries(${PROJECT_NAME} glfw vulkan)
endif()


