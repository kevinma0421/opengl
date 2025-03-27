#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glad/glad.h>

class Shader
{
public:
    Shader(const char *vertexPath, const char *fragmentPath);
    void use() const;

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

    void setVec4(const std::string &name, float r, float g, float b, float a) const;
    void setTexture(const char *vertexPath);

private:
    unsigned int ID;
};

#endif
