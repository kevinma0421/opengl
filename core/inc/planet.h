#ifndef PLANET_H
#define PLANET_H

#include <string>
#include <glad/glad.h>

#include "Sphere.h"

class Planet : public Sphere
{
public:
    // needs to be changed
    Planet(const char *texturePath);
};

#endif