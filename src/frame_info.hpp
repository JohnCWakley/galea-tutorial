#pragma once

#include "camera.hpp"

#include <vulkan/vulkan.h>

namespace ve {
    struct FrameInfo {
        int frameIndex;
        float frameTime;
        VkCommandBuffer commandBuffer;
        Camera& camera;
    };
}