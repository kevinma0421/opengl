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
const char *earthPath = "C:/Users/123ke/projects/opengl/textures/earth10kcopy.jpg";

int main()
{
    static bool pWasPressed = false;

    // Create objects
    Window myWindow(width, height, "sat_sim");
    Shader myShader(vertexPath, fragmentPath);
    Sphere mySphere(1.0f, 100, 100);
    Camera myCamera(static_cast<float>(width), static_cast<float>(height));

    // GL Inits
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glfwSetWindowUserPointer(myWindow.getGLFWwindow(), &myCamera);

    glfwSetScrollCallback(myWindow.getGLFWwindow(), Window::scroll_callback);
    glfwSetMouseButtonCallback(myWindow.getGLFWwindow(), Window::mouse_button_callback);
    glfwSetCursorPosCallback(myWindow.getGLFWwindow(), Window::cursor_position_callback);

    GLuint sphereTexture = mySphere.setTexture(earthPath);

    // Set planet tilt and rotation speed (to be modifed later with GUI)
    float spinSpeed = 2 * glm::pi<float>() / 10.0f;
    float tilt = 23.5f;
    while (!myWindow.shouldClose())
    {
        // ----------- 1. Handle inputs ----------
        processInput(myWindow.getGLFWwindow());

        // ----------- 2. Prepare frame ----------
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ----------- 3. Set common shader uniforms ----------
        glm::mat4 model = mySphere.rotate(myShader, spinSpeed, tilt);
        myShader.use();
        myShader.setMat4("projection", myCamera.getProjectionMatrix());
        myShader.setMat4("view", myCamera.getViewMatrix());

        // ----------- 4. Bind textures ----------
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sphereTexture);

        // ----------- 5. Render base filled sphere ----------
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        mySphere.render(myShader, model);

        // ----------- 6. Render wireframe overlay on top ----------
        glEnable(GL_POLYGON_OFFSET_LINE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        myShader.use();
        mySphere.render(myShader, model);

        myWindow.swapBuffers();
        myWindow.pollEvents();
        static double lastTime = glfwGetTime();
        static int frameCount = 0;

        double currentTime = glfwGetTime();
        frameCount++;

        if (currentTime - lastTime >= 1.0)
        {
            logMessage(std::to_string(frameCount));
            frameCount = 0;
            lastTime = currentTime;
        }
    }

    return 0;
}
