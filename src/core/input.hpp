#pragma once

#include "window.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <spdlog/spdlog.h>
#include <functional>
#include <map>

namespace ve
{
    using KeyPressedHandlerFunction = std::function<void(int, int)>;
    using ButtonClickedHandlerFunction = std::function<void(int, int)>;

    class Input
    {
    public:
        Input(GLFWwindow *window);

        void setEventHandler();
        bool getKeyDown(int key);

        void setKeyPressedHandler(KeyPressedHandlerFunction);
        void setButtonClickedHandler(ButtonClickedHandlerFunction);

    private:
        static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
        static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
        static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);

        void onKeyboardEvent(int key, int scancode, int action, int mods);
        void onMouseButtonEvent(int button, int action, int mods);
        void onMouseWheelEvent(double xoffset, double yoffset);
        void onMouseMoveEvent(double xpos, double ypos);

        int downTimeThreshold{250};

        bool keyDown[GLFW_KEY_LAST + 1] = {false};
        long long keyDownTime[GLFW_KEY_LAST + 1] = {0};

        bool buttonDown[GLFW_MOUSE_BUTTON_LAST + 1] = {false};
        long long buttonDownTime[GLFW_MOUSE_BUTTON_LAST + 1] = {0};

        glm::vec2 mousePosition{0.f};

        KeyPressedHandlerFunction pressedHandler;
        ButtonClickedHandlerFunction clickedHandler;
    };
}