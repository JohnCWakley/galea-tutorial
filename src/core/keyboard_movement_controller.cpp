#include "keyboard_movement_controller.hpp"

namespace ve
{
    void KeyboardMovementController::moveInPlaneXZ(Input input, float dt, GameObject &gameObject)
    {
        glm::vec3 rotate{0};

        if (input.getKeyDown(keys.lookRight)) rotate.y += 1.f;
        if (input.getKeyDown(keys.lookLeft)) rotate.y -= 1.f;
        if (input.getKeyDown(keys.lookUp)) rotate.x += 1.f;
        if (input.getKeyDown(keys.lookDown)) rotate.x -= 1.f;

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

        if (input.getKeyDown(keys.moveForward)) moveDir += forwardDir;
        if (input.getKeyDown(keys.moveBackward)) moveDir -= forwardDir;
        if (input.getKeyDown(keys.moveRight)) moveDir += rightDir;
        if (input.getKeyDown(keys.moveLeft)) moveDir -= rightDir;
        if (input.getKeyDown(keys.moveUp)) moveDir += upDir;
        if (input.getKeyDown(keys.moveDown)) moveDir -= upDir;

        if (glm::dot(moveDir, moveDir) > std::numeric_limits<float>::epsilon())
        {
            gameObject.transform.translation += moveSpeed * dt * glm::normalize(moveDir);
        }
    }
}