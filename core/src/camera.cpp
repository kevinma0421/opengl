#include "camera.h"

Camera::Camera(float screenWidth, float screenHeight, glm::vec3 position, glm::vec3 target, glm::vec3 up)
    : position(position), target(target), up(up), screenWidth(screenWidth), screenHeight(screenHeight) {}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(position, target, up);
}

glm::mat4 Camera::getProjectionMatrix() const
{
    return glm::perspective(glm::radians(fov), screenWidth / screenHeight, nearPlane, farPlane);
}

void Camera::setPosition(const glm::vec3 &pos)
{
    position = pos;
}

void Camera::setTarget(const glm::vec3 &tgt)
{
    target = tgt;
}
void Camera::setScreenSize(float w, float h)
{
    screenWidth = w;
    screenHeight = h;
}
