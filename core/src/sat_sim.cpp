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
#include "skybox.h"

// window sizes
const int height = 800;
const int width = 800;

// Shader Paths
const char *earthvs = "C:/Users/123ke/projects/opengl/shaders/earth.vs";
const char *earthfs = "C:/Users/123ke/projects/opengl/shaders/earth.fs";
const char *skyboxfs = "C:/Users/123ke/projects/opengl/shaders/skybox.fs";
const char *skyboxvs = "C:/Users/123ke/projects/opengl/shaders/skybox.vs";
const char *earthPath = "C:/Users/123ke/projects/opengl/textures/earth10kcopy.jpg";

// Cubemap Paths
const char *space_back = "C:/Users/123ke/projects/opengl/textures/skybox/space_bk.png";
const char *space_bottom = "C:/Users/123ke/projects/opengl/textures/skybox/space_dn.png";
const char *space_front = "C:/Users/123ke/projects/opengl/textures/skybox/space_ft.png";
const char *space_left = "C:/Users/123ke/projects/opengl/textures/skybox/space_lf.png";
const char *space_right = "C:/Users/123ke/projects/opengl/textures/skybox/space_rt.png";
const char *space_top = "C:/Users/123ke/projects/opengl/textures/skybox/space_up.png";

// Skybox init
const std::vector<std::string> skyboxFaces = {
    space_right,  // +X
    space_left,   // -X
    space_top,    // +Y
    space_bottom, // -Y
    space_front,  // +Z
    space_back    // -Z
};
int main()
{
    // Create objects
    Window myWindow(width, height, "sat_sim");
    Planet earth(earthPath, earthvs, earthfs);
    Camera myCamera(static_cast<float>(width), static_cast<float>(height));
    Gui myGui(myWindow.getGLFWwindow());
    Skybox skybox(skyboxFaces, skyboxvs, skyboxfs);

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
        // earth.renderEarth(myCamera);

        // render cubeMap
        skybox.render(myCamera);

        // render Gui
        myGui.render();

        myWindow.swapBuffers();
        myWindow.pollEvents();
    }

    return 0;
}
