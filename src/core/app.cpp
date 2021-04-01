#include "app.hpp"

namespace ve {
    void App::run() {
        while (!window.shouldClose()) {
            glfwPollEvents();
        }
    }
}