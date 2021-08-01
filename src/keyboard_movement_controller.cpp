#include "keyboard_movement_controller.hpp"

namespace ve
{
    void KeyboardMovementController::moveInPlaneXZ(ezi::Input input, float dt, GameObject &gameObject)
    {
        glm::vec3 rotate{0};

        if (input.isMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT))
        {
            rotate.y -= input.getMousePositionOffset().x;
            rotate.x += input.getMousePositionOffset().y;
        }
        else
        {
            rotate.y += (float)(input.isKeyDown(keys.lookRight) - input.isKeyDown(keys.lookLeft));
            rotate.x += (float)(input.isKeyDown(keys.lookUp) - input.isKeyDown(keys.lookDown));
        }

        if (glm::dot(rotate, rotate) > std::numeric_limits<float>::epsilon())
        {
            gameObject.transform.rotation += lookSpeed * dt * glm::normalize(rotate);
        }

        gameObject.transform.rotation.x = glm::clamp(gameObject.transform.rotation.x, -1.5f, 1.5f);
        gameObject.transform.rotation.y = glm::mod(gameObject.transform.rotation.y, glm::two_pi<float>());

        float yaw = gameObject.transform.rotation.y;
        const glm::vec3 forwardDir{sin(yaw), 0.f, cos(yaw)};
        const glm::vec3 rightDir{forwardDir.z, 0.f, -forwardDir.x};
        const glm::vec3 upDir{0.f, -1.f, 0.f};

        glm::vec3 moveDir{0.f};

        moveDir += forwardDir * (float)(input.isKeyDown(keys.moveForward) - input.isKeyDown(keys.moveBackward));
        moveDir += rightDir * (float)(input.isKeyDown(keys.moveRight) - input.isKeyDown(keys.moveLeft));
        moveDir += upDir * (float)(input.isKeyDown(keys.moveUp) - input.isKeyDown(keys.moveDown));

        if (glm::dot(moveDir, moveDir) > std::numeric_limits<float>::epsilon())
        {
            gameObject.transform.translation += moveSpeed * dt * glm::normalize(moveDir);
        }
    }
}