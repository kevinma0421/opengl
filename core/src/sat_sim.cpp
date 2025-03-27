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
const char *earth = "C:/Users/123ke/projects/opengl/textures/earth4k.jpg";

int main()
{
    static bool pWasPressed = false;

    // Create objects
    Window myWindow(800, 800, "sat_sim");
    Shader myShader(vertexPath, fragmentPath);
    Sphere mySphere(1.0f, 50, 50);

    // GL Inits
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    GLuint sphereTexture = mySphere.setTexture(earth);

    // Main render loop
    while (!myWindow.shouldClose())
    {
        if (glfwGetKey(myWindow.getGLFWwindow(), GLFW_KEY_P) == GLFW_PRESS)
        {
            if (!pWasPressed)
            {
                togglePolygonMode();
                pWasPressed = true;
            }
        }
        else
        {
            pWasPressed = false;
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        myShader.use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sphereTexture);
        myShader.setInt("sphereTexture", 0);
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
