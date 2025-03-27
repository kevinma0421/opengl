#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <fstream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "stb.h"
#include <planet.h>

Planet::Planet(const char *vertexPath) : Sphere(1.0f, 50, 50)
{
}
