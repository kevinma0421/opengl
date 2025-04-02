#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "camera.h"
#include "utils.h"

class Gui
{
public:
    Gui(GLFWwindow *window);
    ~Gui();
    void frame(Camera &camera, float &rotationSpeed);
    void render();
    int fps();
};
