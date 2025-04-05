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
    Skybox(const char *skyboxfs, const char *skyboxvs);
    void render(Camera &camera);

private:
    GLuint skyboxVAO, skyboxVBO;
    GLuint cubemapTexture = 0;
    Shader skyboxShader;

    GLuint loadTexture();
    void setupBuffers();

    // Cubemap Paths
    const char *space_1 = "C:/Users/123ke/projects/opengl/textures/skybox/space_bk.png";
    const char *space_2 = "C:/Users/123ke/projects/opengl/textures/skybox/space_ft.png";
    const char *space_3 = "C:/Users/123ke/projects/opengl/textures/skybox/space_dn.png";
    const char *space_4 = "C:/Users/123ke/projects/opengl/textures/skybox/space_up.png";
    const char *space_5 = "C:/Users/123ke/projects/opengl/textures/skybox/space_lf.png";
    const char *space_6 = "C:/Users/123ke/projects/opengl/textures/skybox/space_rt.png";

    // Skybox init
    std::vector<std::string> faces = {
        space_1,
        space_2,
        space_3,
        space_4,
        space_5,
        space_6};
};
