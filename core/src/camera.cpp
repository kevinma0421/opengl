#include "camera.h"

Camera::Camera(float screenWidth, float screenHeight,
               float radius, float yaw, float pitch,
               glm::vec3 center, glm::vec3 up)
    : screenWidth(screenWidth),
      screenHeight(screenHeight),
      radius(radius),
      yaw(yaw),
      pitch(pitch),
      center(center),
      up(up)
{
}

glm::mat4 Camera::getViewMatrix() const
{
    float x = center.x + radius * cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    float y = center.y + radius * sin(glm::radians(pitch));
    float z = center.z + radius * cos(glm::radians(pitch)) * sin(glm::radians(yaw));

    glm::vec3 cameraPos = glm::vec3(x, y, z);
    return glm::lookAt(cameraPos, center, up);
}

glm::mat4 Camera::getProjectionMatrix() const
{
    float aspect = (screenHeight != 0)
                       ? static_cast<float>(screenWidth) / static_cast<float>(screenHeight)
                       : 1.0f;

    return glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
}

void Camera::setScreenSize(float w, float h)
{
    screenWidth = w;
    screenHeight = h;
}
void Camera::processScroll(float yOffset)
{
    radius -= yOffset;
    radius = glm::clamp<float>(radius, 2.0f, 15.0f);
}
void Camera::setMouse(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            isDragging = true;
            glfwGetCursorPos(window, &lastX, &lastY);
        }
        else if (action == GLFW_RELEASE)
        {
            isDragging = false;
        }
    }
}
void Camera::setCursor(GLFWwindow *window, double xpos, double ypos)
{
    if (isDragging)
    {
        float dx = static_cast<float>(xpos - lastX);
        float dy = static_cast<float>(ypos - lastY);

        lastX = xpos;
        lastY = ypos;

        yaw += dx * sensitivity;
        pitch += dy * sensitivity;

        pitch = glm::clamp(pitch, -89.0f, 89.0f); // prevent flip
    }
}
void Camera::reset()
{
    radius = 5.0f;
    yaw = -90.0f;
    pitch = 0.0f;
}
glm::vec3 Camera::getPosition() const
{
    float x = center.x + radius * cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    float y = center.y + radius * sin(glm::radians(pitch));
    float z = center.z + radius * cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    return glm::vec3(x, y, z);
}
