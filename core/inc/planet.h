#pragma once

#include <string>
#include <glad/glad.h>

#include "Sphere.h"
#include "camera.h"

class Planet : public Sphere
{
public:
    float tilt;
    float rotationSpeed;

    Planet(const char *texturePath);

    void renderEarth(Shader &shader, Camera &camera);
    void update();

private:
    GLuint planetTexture;
    float currentAngle = 0.0f;
    float lastUpdateTime = 0.0f;
};
