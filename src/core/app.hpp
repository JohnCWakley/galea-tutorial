#pragma once

#include "window.hpp"
#include "pipeline.hpp"

namespace ve
{
    class App
    {
    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;

        void run();

    private:
        Window window{WIDTH, HEIGHT, "VulkanEngine"};
        Pipeline pipeline{"../src/shaders/simple_shader.vert.spv", "../src/shaders/simple_shader.frag.spv"};
    };
}
