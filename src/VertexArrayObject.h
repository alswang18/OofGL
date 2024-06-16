#pragma once
#include <glad/glad.h>

class VertexBufferObject;

class VertexArrayObject {
public:
    GLuint id;
    VertexArrayObject();
    void LinkAttrib(VertexBufferObject& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
    void Bind();
    void Unbind();
    void Delete();
    ~VertexArrayObject();
};
