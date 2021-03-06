#pragma once

#include <ezi/input.hpp>
#include "device.hpp"
#include "game_object.hpp"
#include "renderer.hpp"
#include "window.hpp"

// std
#include <memory>
#include <vector>

namespace ve {
    class App {
    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;

        App();
        ~App();

        App(const App&) = delete;
        App& operator=(const App&) = delete;

        void run();

    private:
        void loadGameObjects();

        Window window{ WIDTH, HEIGHT, "Vulkan Tutorial" };
        Device device{ window };
        Renderer renderer{ window, device };
        ezi::Input input{};

        std::vector<GameObject> gameObjects;
    };
}