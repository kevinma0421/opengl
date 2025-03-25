#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <string>

class Window
{
public:
    Window(int width, int height, const std::string &title);
    ~Window();

    void swapBuffers();
    void pollEvents();
    bool shouldClose() const;

    GLFWwindow *getGLFWwindow() const;

private:
    GLFWwindow *window;
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
};

#endif
