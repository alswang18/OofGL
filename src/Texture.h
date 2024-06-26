#pragma once
#include "ShaderProgram.h"
#include "glad/glad.h"

class Texture {
public:
    GLuint id;
    GLenum type;
    Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
    void texUnit(ShaderProgram& shader, const char* uniform, GLuint unit);
    void Bind();
    void Unbind();
    void Delete();
    ~Texture();
};