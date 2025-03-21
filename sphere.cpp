#define _USE_MATH_DEFINES

#include "Sphere.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

Sphere::Sphere(float radius, int stacks, int slices) : radius(radius), stacks(stacks), slices(slices)
{
    generateSphere();
    setupBuffers();
}

Sphere::~Sphere()
{
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}

void Sphere::generateSphere()
{
    vertices.clear();
    indices.clear();

    for (int i = 0; i <= stacks; i++)
    {
        float lat = M_PI * (-0.5f + (float)i / stacks);
        float y = sin(lat);
        float zr = cos(lat);

        for (int j = 0; j <= slices; j++)
        {
            float lon = 2 * M_PI * (float)j / slices;
            float x = cos(lon) * zr;
            float z = sin(lon) * zr;

            // Store vertex positions
            vertices.push_back(x * radius);
            vertices.push_back(y * radius);
            vertices.push_back(z * radius);

            // UV coordinates
            vertices.push_back((float)j / slices);
            vertices.push_back((float)i / stacks);
        }
    }

    for (int i = 0; i < stacks; i++)
    {
        for (int j = 0; j < slices; j++)
        {
            int first = (i * (slices + 1)) + j;
            int second = first + slices + 1;

            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }
}

void Sphere::setupBuffers()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // UV attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Sphere::render()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
