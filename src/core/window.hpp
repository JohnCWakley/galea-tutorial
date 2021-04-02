#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace ve
{
    class Window
    {
    public:
        Window(int, int, std::string);
        ~Window();

        Window(const Window &) = delete;
        Window &operator=(const Window &) = delete;

        bool shouldClose() { return glfwWindowShouldClose(window); }
        VkExtent2D getExtent() { return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; }

        void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

    private:
        void initialize();

        const int width;
        const int height;

        std::string name;
        GLFWwindow *window;
    };
}
