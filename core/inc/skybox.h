#pragma once

#include <vector>
#include <string>
#include <glad/glad.h>
#include <glm.hpp>
#include "shader.h" // Your shader wrapper class
#include "stb.h"
#include "camera.h"

class Skybox
{
public:
    Skybox(const std::vector<std::string> &faces, const char *skyboxfs, const char *skyboxvs);
    void render(Camera camera);

private:
    GLuint skyboxVAO, skyboxVBO;
    GLuint cubemapTexture;
    Shader skyboxShader;

    GLuint loadCubemap(const std::vector<std::string> &faces);
    void setupBuffers();
};
