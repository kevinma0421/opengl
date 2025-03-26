#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <fstream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "sat_sim.h"
#include "sphere.h"
#include "utils.h"
#include "shader.h"
#include "window.h"
#include "stb.h"

// Shader Paths
const char *vertexPath = "C:/Users/123ke/projects/opengl/shaders/vertex_shader.vs";
const char *fragmentPath = "C:/Users/123ke/projects/opengl/shaders/fragment_shader.fs";
const char *texturePath = "C:/Users/123ke/projects/opengl/textures/earth4k.jpg";

int main()
{
    // logMessage("hello world!");

    // Create objects
    Window myWindow(800, 800, "sat_sim");
    Shader myShader(vertexPath, fragmentPath);
    Sphere mySphere(1.0f, 50, 50);

    // GL Inits
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Load Earth Texture
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 0);

    GLuint earthTexture;
    glGenTextures(1, &earthTexture);
    glBindTexture(GL_TEXTURE_2D, earthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
                 nrChannels == 4 ? GL_RGBA : GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    // Texture settings
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Main render loop
    while (!myWindow.shouldClose())
    {
        if (glfwGetKey(myWindow.getGLFWwindow(), GLFW_KEY_P) == GLFW_PRESS)
            togglePolygonMode();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        myShader.use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, earthTexture);
        myShader.setInt("earthTexture", 0);

        mySphere.render();

        myWindow.pollEvents();
        myWindow.swapBuffers();
    }

    return 0;
}
void togglePolygonMode()
{
    static bool wireframe = false;
    wireframe = !wireframe;

    if (wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
