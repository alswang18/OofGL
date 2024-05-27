#pragma once
#include <glad/glad.h>

class ShaderManager {
public:
    ShaderManager();
    ~ShaderManager();
    ShaderManager(const ShaderManager&) = delete;
    ShaderManager& operator=(const ShaderManager&) = delete;

    bool compileShaders();
    void useShaderProgram() const;

    bool getShouldCompileShader() const { return shouldCompileShader; }
    void triggerShaderCompile() { shouldCompileShader = true; }

private:
    bool shouldCompileShader = true;
    GLuint shaderProgram;
};