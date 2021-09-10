#include "app.hpp"

#include "keyboard_movement_controller.hpp"
#include "camera.hpp"
#include "simple_render_system.hpp"
#include "logger.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

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

        input.init(window.getWindow());

        input.addListener("key_down", [](int key, int mods)
                          { log_debug("key_down: ", key); });

        input.addListener("key_up", [](int key, int mods)
                          { log_debug("key_up: ", key); });

        input.addListener("key_pressed", [this](int key, int mods)
                          {
                              if (key == GLFW_KEY_ESCAPE)
                              {
                                  window.close();
                              }
                              else
                              {
                                  log_debug("key_pressed: ", key);
                              }
                          });

        input.addListener("button_down", [](int button, int mods)
                          { log_debug("button_down: ", button); });

        input.addListener("button_up", [](int button, int mods)
                          { log_debug("button_up: ", button); });

        input.addListener("button_clicked", [](int button, int mods)
                          { log_debug("button_clicked: ", button); });

        input.addListener("wheel_left", [](int offset)
                          { log_debug("wheel_left: ", offset); });

        input.addListener("wheel_right", [](int offset)
                          { log_debug("wheel_right: ", offset); });

        input.addListener("wheel_up", [](int offset)
                          { log_debug("wheel_up: ", offset); });

        input.addListener("wheel_down", [](int offset)
                          { log_debug("wheel_down: ", offset); });

        input.addListener("mouse_moved", [this](glm::vec2 position, glm::vec2 offset)
                          {
                              if (input.isMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT))
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
        }

        vkDeviceWaitIdle(device.device());
    }

    void App::loadGameObjects()
    {
        std::shared_ptr<Model> model = Model::createModelFromFile(device, "../models/smooth_vase.obj");
        auto gameObject = GameObject::createGameObject();
        gameObject.model = model;
        gameObject.transform.translation = {.0f, .0f, 2.5f};
        gameObject.transform.scale = glm::vec3(3.f);
        gameObjects.push_back(std::move(gameObject));
    }

}