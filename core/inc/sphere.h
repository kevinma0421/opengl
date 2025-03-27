#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include <glad/glad.h> // OpenGL functions
// #include <glm/glm.hpp> // Math library

class Sphere
{
public:
    Sphere(float radius, int stacks, int slices); // Constructor
    ~Sphere();                                    // Destructor

    void generateSphere(); // Function to generate vertices & indices
    void setupBuffers();   // Function to set up OpenGL buffers
    void render();         // Function to render the sphere
    GLuint setTexture(const char *texturePath);

private:
    float radius;
    int stacks, slices;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    unsigned int VAO, VBO, EBO;
};

#endif
