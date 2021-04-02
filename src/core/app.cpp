#include "app.hpp"

namespace ve
{
    void App::run()
    {
        while (!window.shouldClose())
        {
            glfwPollEvents();
        }
    }

    void App::createPipelineLayout() {}
    void App::createPipeline() {}
    void App::createCommandBuffers() {}
    void App::drawFrame() {}
}
