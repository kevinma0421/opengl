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
    static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
    static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
    static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);

private:
    GLFWwindow *window;
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
};
#endif
