#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "camera.h"
#include "utils.h"
#include "stb.h"

class Gui
{
public:
    Gui(GLFWwindow *window);
    ~Gui();
    void frame(Camera &camera, float &rotationSpeed);
    void render();
    int fps();
    GLuint LoadTexture(const char *filename);
    int speedMultiplier;
    int speedOptions[2];
    GLuint speedButtons[2];
    int currIndex;
    const char *forward;
    const char *pause;
    const char *play;
};
