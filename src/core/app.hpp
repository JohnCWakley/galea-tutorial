#pragma once

#include "pipeline.hpp"
#include "window.hpp"
#include "device.hpp"

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
        Device device{window};
        Pipeline pipeline{device, "../src/shaders/simple_shader.vert.spv", "../src/shaders/simple_shader.frag.spv", Pipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};
    };
}
