#include "input.h"

static bool wireframe = true;
static bool pKeyPressed = false;

void processInput(GLFWwindow *window)
{
    togglePoly(window);
    closeWindow(window);
}
void togglePoly(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && !pKeyPressed)
    {
        wireframe = !wireframe;
        glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
        pKeyPressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE)
    {
        pKeyPressed = false;
    }
}
void closeWindow(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
void rotationSpeed(GLFWwindow *window)
{
}