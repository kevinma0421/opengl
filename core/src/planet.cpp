#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <fstream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "stb.h"
#include <planet.h>

Planet::Planet(const char *texturePath) : Sphere(1.0f, 100, 100)
{
    this->planetTexture = this->setTexture(texturePath);

    rotationSpeed = 2 * glm::pi<float>() / 86164.0f;
    tilt = 23.5f;
}
void Planet::renderEarth(Shader &shader, Camera &camera)
{
    this->update();
    // set texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, planetTexture);

    glm::mat4 model = this->rotate(shader, this->tilt, this->currentAngle);
    shader.use();
    shader.setMat4("projection", camera.getProjectionMatrix());
    shader.setMat4("view", camera.getViewMatrix());

    // Render solid sphere
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    this->render(shader, model);

    // Render wire overlay on top
    glEnable(GL_POLYGON_OFFSET_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    shader.use();
    this->render(shader, model);
}
void Planet::update()
{
    float currentTime = glfwGetTime();
    float deltaTime = currentTime - lastUpdateTime;
    lastUpdateTime = currentTime;

    currentAngle += rotationSpeed * deltaTime;
}