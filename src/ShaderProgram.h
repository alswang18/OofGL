#pragma once

#include <fstream>
#include <glad/glad.h>
#include <sstream>
#include <string>

class ShaderProgram {
public:
    ShaderProgram();
    ShaderProgram(const std::string& vertex, const std::string& fragment);
    ~ShaderProgram();
    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram& operator=(const ShaderProgram&) = delete;

    void setShader(const std::string& vertex, const std::string& fragment);
    void useShaderProgram() const;

    bool isShaderReady() const { return shaderReady; }

private:
    bool compileShaders(const std::string& vertex, const std::string& fragment);
    bool shaderReady = false;
    GLuint shaderProgram;
};