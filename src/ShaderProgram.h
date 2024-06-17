#pragma once

#include <glad/glad.h>
#include <string>

class ShaderProgram {
public:
    ShaderProgram();
    ShaderProgram(const std::string& vertex, const std::string& fragment);
    ~ShaderProgram();
    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram& operator=(const ShaderProgram&) = delete;

    void reloadShader();
    void use() const;

    bool isShaderReady() const { return shaderReady; }
    GLuint getShaderId() const { return shaderId; }

private:
    bool compileShaders(const std::string& vertex, const std::string& fragment);
    bool shaderReady = false;
    GLuint shaderId;
    std::string vertexName;
    std::string fragmentName;
    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
};