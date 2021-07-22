#include "input.hpp"

#include <spdlog/spdlog.h>
#include <chrono>
#include <iostream>

namespace ve
{
    Input::Input(GLFWwindow *window)
    {
        glfwSetWindowUserPointer(window, this);
        glfwSetKeyCallback(window, &Input::key_callback);
        glfwSetMouseButtonCallback(window, &Input::mouse_button_callback);
        glfwSetScrollCallback(window, &Input::scroll_callback);
        glfwSetCursorPosCallback(window, &Input::cursor_position_callback);
    }

    void Input::setEventHandler()
    {
    }

    bool Input::getKeyDown(int key)
    {
        return keyDown[key];
    }

    bool Input::getButtonDown(int button)
    {
        return buttonDown[button];
    }

    void Input::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        static_cast<Input *>(glfwGetWindowUserPointer(window))->onKeyboardEvent(key, scancode, action, mods);
    }

    void Input::mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
    {
        static_cast<Input *>(glfwGetWindowUserPointer(window))->onMouseButtonEvent(button, action, mods);
    }

    void Input::scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
    {
        static_cast<Input *>(glfwGetWindowUserPointer(window))->onMouseWheelEvent(xoffset, yoffset);
    }

    void Input::cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
    {
        static_cast<Input *>(glfwGetWindowUserPointer(window))->onMouseMoveEvent(xpos, ypos);
    }

    long long _now()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }

    void Input::onKeyboardEvent(int key, int scancode, int action, int mods)
    {
        long long now = _now();

        if (action == GLFW_PRESS)
        {
            spdlog::debug("key down: {}", key);
            keyDown[key] = true;
            keyDownTime[key] = now;
        }
        else if (action == GLFW_RELEASE)
        {
            keyDown[key] = false;

            if (now - keyDownTime[key] < downTimeThreshold)
            {
                spdlog::debug("key pressed: {}", key);
                emit("key_pressed", key, mods);
            }
            else
            {
                spdlog::debug("key up: {}", key);
            }

            keyDownTime[key] = 0;
        }
    }

    void Input::onMouseButtonEvent(int button, int action, int mods)
    {
        long long now = _now();

        if (action == GLFW_PRESS)
        {
            spdlog::debug("button down: {}", button);
            buttonDown[button] = true;
            buttonDownTime[button] = now;
        }
        else if (action == GLFW_RELEASE)
        {
            buttonDown[button] = false;

            if (now - buttonDownTime[button] < downTimeThreshold)
            {
                spdlog::debug("button clicked: {}", button);
                emit("button_clicked", button, mods);
            }
            else
            {
                spdlog::debug("button up: {}", button);
            }

            buttonDownTime[button] = 0;
        }
    }

    void Input::onMouseWheelEvent(double xoffset, double yoffset)
    {
        spdlog::debug(
            "onMouseWheelEvent: xoffset: {0}, yoffset: {1}",
            xoffset, yoffset);
    }

    void Input::onMouseMoveEvent(double xpos, double ypos)
    {
        // spdlog::debug(
        //     "onMouseMoveEvent: xpos: {0}, ypos: {1}",
        //     xpos, ypos
        // );
        mousePositionOffset.x = mousePosition.x - xpos;
        mousePositionOffset.y = mousePosition.y - ypos;
        mousePosition.x = xpos;
        mousePosition.y = ypos;

        emit("mouse_moved", mousePosition, mousePositionOffset);
    }
}