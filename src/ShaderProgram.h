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
    void reloadShader();
    void useShaderProgram() const;

    bool isShaderReady() const { return shaderReady; }
    GLuint getShaderProgram() const { return shaderProgram; }

private:
    bool compileShaders(const std::string& vertex, const std::string& fragment);
    bool shaderReady = false;
    GLuint shaderProgram;
    std::string vertexName;
    std::string fragmentName;
    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
};