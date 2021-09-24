#pragma once

#include "camera.hpp"
#include "device.hpp"
#include "game_object.hpp"
#include "pipeline.hpp"
#include "frame_info.hpp"

#include <memory>
#include <vector>

namespace ve {
    class SimpleRenderSystem {
    public:
        SimpleRenderSystem(Device& device, VkRenderPass renderPass);
        ~SimpleRenderSystem();

        SimpleRenderSystem(const SimpleRenderSystem&) = delete;
        SimpleRenderSystem& operator=(const SimpleRenderSystem&) = delete;

        void renderGameObjects(FrameInfo& frameInfo, std::vector<GameObject>& gameObjects);

    private:
        void createPipelineLayout();
        void createPipeline(VkRenderPass renderPass);

        Device& device;

        std::unique_ptr<Pipeline> pipeline;
        VkPipelineLayout pipelineLayout;
    };
}