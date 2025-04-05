#pragma once

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
    void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
    unsigned int ID;
};
