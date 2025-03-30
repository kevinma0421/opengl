#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Camera
{
public:
    Camera(float screenWidth, float screenHeight,
           glm::vec3 position = glm::vec3(0.0f, 0.0f, 7.0f),
           glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

    void setPosition(const glm::vec3 &pos);
    void setTarget(const glm::vec3 &tgt);

private:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;
    float screenWidth;
    float screenHeight;
    float fov = 45.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
};
