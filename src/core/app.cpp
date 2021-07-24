#include "app.hpp"

#include "keyboard_movement_controller.hpp"
#include "camera.hpp"
#include "simple_render_system.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <spdlog/spdlog.h>
#include <array>
#include <chrono>
#include <cassert>
#include <stdexcept>

namespace ve
{
    const float MAX_FRAME_TIME = 1.f;

    App::App()
    {
        loadGameObjects();

        input.addListener("key_down", [](int key, int mods)
                          { std::cout << "key_down: " << key << std::endl; });

        input.addListener("key_up", [](int key, int mods)
                          { std::cout << "key_up: " << key << std::endl; });

        input.addListener("key_pressed", [this](int key, int mods)
                          {
                              if (key == GLFW_KEY_ESCAPE)
                              {
                                  window.close();
                              }
                              else
                              {
                                  std::cout << "key_pressed: " << key << std::endl;
                              }
                          });

        input.addListener("button_down", [](int button, int mods)
                          { std::cout << "button_down: " << button << std::endl; });

        input.addListener("button_up", [](int button, int mods)
                          { std::cout << "button_up: " << button << std::endl; });

        input.addListener("button_clicked", [](int button, int mods)
                          { std::cout << "button_clicked: " << button << std::endl; });

        input.addListener("button_clicked", [](int button, int mods)
                          { std::cout << "button_clicked: " << button << std::endl; });

        input.addListener("wheel_left", [](int offset)
                          { std::cout << "wheel_left: " << offset << std::endl; });

        input.addListener("wheel_right", [](int offset)
                          { std::cout << "wheel_right: " << offset << std::endl; });

        input.addListener("wheel_up", [](int offset)
                          { std::cout << "wheel_up: " << offset << std::endl; });

        input.addListener("wheel_down", [](int offset)
                          { std::cout << "wheel_down: " << offset << std::endl; });

        input.addListener("mouse_moved", [this](glm::vec2 position, glm::vec2 offset)
                          {
                              if (input.getButtonDown(GLFW_MOUSE_BUTTON_LEFT))
                              {
                                  std::cout << "mouse_moved: px: " << position.x << ", py: " << position.y
                                            << ", ox: " << offset.x << ", oy: " << offset.y << std::endl;
                              }
                          });
    }

    App::~App() {}

    void App::run()
    {
        SimpleRenderSystem simpleRenderSystem{device, renderer.getSwapChainRenderPass()};

        Camera camera{};
        camera.setViewDirection(glm::vec3{0.f}, glm::vec3{0.f, 0.f, 1.f});

        auto viewerObject = GameObject::createGameObject();
        KeyboardMovementController cameraController{};

        auto currentTime = std::chrono::high_resolution_clock::now();

        while (!window.shouldClose())
        {
            glfwPollEvents();

            auto newTime = std::chrono::high_resolution_clock::now();
            float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
            frameTime = glm::min(frameTime, MAX_FRAME_TIME);
            currentTime = newTime;

            cameraController.moveInPlaneXZ(input, frameTime, viewerObject);
            camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

            float aspect = renderer.getAspectRatio();
            camera.setPerspectiveProjection(glm::radians(50.f), aspect, 0.1f, 10.f);

            if (auto commandBuffer = renderer.beginFrame())
            {
                renderer.beginSwapChainRenderPass(commandBuffer);
                simpleRenderSystem.renderGameObjects(commandBuffer, gameObjects, camera);
                renderer.endSwapChainRenderPass(commandBuffer);
                renderer.endFrame();
            }

            input.update();
        }

        vkDeviceWaitIdle(device.device());
    }

    // temporary helper function, creates a 1x1x1 cube centered at offset
    std::unique_ptr<Model> createCubeModel(Device &device, glm::vec3 offset)
    {
        std::vector<Model::Vertex> vertices{
            // left face (white)
            {{-.5f, -.5f, -.5f}, {.9f, .9f, .9f}},
            {{-.5f, .5f, .5f}, {.9f, .9f, .9f}},
            {{-.5f, -.5f, .5f}, {.9f, .9f, .9f}},
            {{-.5f, -.5f, -.5f}, {.9f, .9f, .9f}},
            {{-.5f, .5f, -.5f}, {.9f, .9f, .9f}},
            {{-.5f, .5f, .5f}, {.9f, .9f, .9f}},

            // right face (yellow)
            {{.5f, -.5f, -.5f}, {.8f, .8f, .1f}},
            {{.5f, .5f, .5f}, {.8f, .8f, .1f}},
            {{.5f, -.5f, .5f}, {.8f, .8f, .1f}},
            {{.5f, -.5f, -.5f}, {.8f, .8f, .1f}},
            {{.5f, .5f, -.5f}, {.8f, .8f, .1f}},
            {{.5f, .5f, .5f}, {.8f, .8f, .1f}},

            // top face (orange, remember y axis points down)
            {{-.5f, -.5f, -.5f}, {.9f, .6f, .1f}},
            {{.5f, -.5f, .5f}, {.9f, .6f, .1f}},
            {{-.5f, -.5f, .5f}, {.9f, .6f, .1f}},
            {{-.5f, -.5f, -.5f}, {.9f, .6f, .1f}},
            {{.5f, -.5f, -.5f}, {.9f, .6f, .1f}},
            {{.5f, -.5f, .5f}, {.9f, .6f, .1f}},

            // bottom face (red)
            {{-.5f, .5f, -.5f}, {.8f, .1f, .1f}},
            {{.5f, .5f, .5f}, {.8f, .1f, .1f}},
            {{-.5f, .5f, .5f}, {.8f, .1f, .1f}},
            {{-.5f, .5f, -.5f}, {.8f, .1f, .1f}},
            {{.5f, .5f, -.5f}, {.8f, .1f, .1f}},
            {{.5f, .5f, .5f}, {.8f, .1f, .1f}},

            // nose face (blue)
            {{-.5f, -.5f, 0.5f}, {.1f, .1f, .8f}},
            {{.5f, .5f, 0.5f}, {.1f, .1f, .8f}},
            {{-.5f, .5f, 0.5f}, {.1f, .1f, .8f}},
            {{-.5f, -.5f, 0.5f}, {.1f, .1f, .8f}},
            {{.5f, -.5f, 0.5f}, {.1f, .1f, .8f}},
            {{.5f, .5f, 0.5f}, {.1f, .1f, .8f}},

            // tail face (green)
            {{-.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
            {{.5f, .5f, -0.5f}, {.1f, .8f, .1f}},
            {{-.5f, .5f, -0.5f}, {.1f, .8f, .1f}},
            {{-.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
            {{.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
            {{.5f, .5f, -0.5f}, {.1f, .8f, .1f}},

        };

        for (auto &v : vertices)
        {
            v.position += offset;
        }

        return std::make_unique<Model>(device, vertices);
    }

    void App::loadGameObjects()
    {
        std::shared_ptr<Model> model = createCubeModel(device, {.0f, .0f, .0f});
        auto cube = GameObject::createGameObject();
        cube.model = model;
        cube.transform.translation = {.0f, .0f, 2.5f};
        cube.transform.scale = {.5f, .5f, .5f};
        gameObjects.push_back(std::move(cube));
    }

}