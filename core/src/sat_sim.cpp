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
#include "input.h"
#include "camera.h"

// window sizes
const int height = 800;
const int width = 800;

// Shader Paths
const char *vertexPath = "C:/Users/123ke/projects/opengl/shaders/vertex_shader.vs";
const char *fragmentPath = "C:/Users/123ke/projects/opengl/shaders/fragment_shader.fs";
const char *earthPath = "C:/Users/123ke/projects/opengl/textures/earth4k.jpg";

int main()
{
    static bool pWasPressed = false;

    // Create objects
    Window myWindow(width, height, "sat_sim");
    Shader myShader(vertexPath, fragmentPath);
    Sphere mySphere(1.0f, 100, 100);
    Camera mycamera(static_cast<float>(width), static_cast<float>(height));

    // GL Inits
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    GLuint sphereTexture = mySphere.setTexture(earthPath);

    while (!myWindow.shouldClose())
    {
        // ----------- 1. Handle inputs ----------
        processInput(myWindow.getGLFWwindow());

        // ----------- 2. Prepare frame ----------
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ----------- 3. Use shaders ----------
        myShader.use();
        myShader.setInt("sphereTexture", 0);
        myShader.setMat4("view", mycamera.getViewMatrix());
        myShader.setMat4("projection", mycamera.getProjectionMatrix());

        // ----------- 4. Bind textures ----------
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sphereTexture);

        // ----------- 6. Render Objects ----------
        mySphere.rotate(myShader, 0.6f, -23.5f);
        mySphere.render(myShader);

        // ----------- 7. Swap Buffers & Poll ----------
        myWindow.swapBuffers();
        myWindow.pollEvents();
    }

    return 0;
}
