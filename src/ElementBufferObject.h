#pragma once

#include <glad/glad.h>

class ElementBufferObject {
public:
    GLuint id;
    ElementBufferObject(GLuint* indices, GLsizeiptr size);
    void Bind();
    void Unbind();
    void Delete();
    ~ElementBufferObject();
};
