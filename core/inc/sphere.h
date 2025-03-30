#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include <glad/glad.h> // OpenGL functions
#include <glm.hpp>     // Math library
#include "shader.h"

class Sphere
{
public:
    Sphere(float radius, int stacks, int slices); // Constructor
    ~Sphere();                                    // Destructor

    void generateSphere();               // Function to generate vertices & indices
    void setupBuffers();                 // Function to set up OpenGL buffers
    void render(const Shader &myShader); // Function to render the sphere
    GLuint setTexture(const char *texturePath);

    void rotate(const Shader &myShader, float speed, float tilt);

private:
    float radius;
    int stacks, slices;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    unsigned int VAO, VBO, EBO;
};

#endif
