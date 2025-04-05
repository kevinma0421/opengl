#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <fstream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "stb.h"
#include <planet.h>

Planet::Planet(const char *texturePath, const char *vertexShader, const char *fragmentShader)
    : Sphere(1.0f, 100, 100),
      shader(vertexShader, fragmentShader),
      planetTexture(setTexture(texturePath))
{
    rotationSpeed = 2 * glm::pi<float>() / 86164.0f;
    tilt = 23.5f;
}
void Planet::renderEarth(Camera &camera)
{
    update();
    // set texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, planetTexture);

    glm::mat4 model = rotate(tilt, currentAngle);
    shader.use();
    shader.setInt("sphereTexture", 0);
    shader.setMat4("projection", camera.getProjectionMatrix());
    shader.setMat4("view", camera.getViewMatrix());
    shader.setMat4("model", model);
    // Render solid sphere
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    render(shader);

    // Render wire overlay on top
    glEnable(GL_POLYGON_OFFSET_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    shader.use();
    render(shader);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void Planet::update()
{
    float currentTime = glfwGetTime();
    float deltaTime = currentTime - lastUpdateTime;
    lastUpdateTime = currentTime;

    currentAngle += rotationSpeed * deltaTime;
}