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
#include "gui.h"
#include "planet.h"

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
    Planet earth(earthPath);
    Camera myCamera(static_cast<float>(width), static_cast<float>(height));
    Gui myGui(myWindow.getGLFWwindow());

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

    while (!myWindow.shouldClose())
    {
        // prep frame
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // input handling
        processInput(myWindow.getGLFWwindow());

        // GUI frame
        myGui.frame(myCamera, earth.rotationSpeed);

        // render Earth
        earth.renderEarth(myShader, myCamera);

        // render Gui
        myGui.render();

        myWindow.swapBuffers();
        myWindow.pollEvents();
    }

    return 0;
}
