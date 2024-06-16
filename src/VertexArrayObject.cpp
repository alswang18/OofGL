#include "VertexArrayObject.h"
#include "VertexBufferObject.h"

VertexArrayObject::VertexArrayObject()
{
    glGenVertexArrays(1, &id);
}

void VertexArrayObject::LinkAttrib(VertexBufferObject& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
    vbo.Bind();
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    vbo.Unbind();
}

void VertexArrayObject::Bind()
{
    glBindVertexArray(id);
}

void VertexArrayObject::Unbind()
{
    glBindVertexArray(0);
}

void VertexArrayObject::Delete()
{
    glDeleteVertexArrays(1, &id);
}

VertexArrayObject::~VertexArrayObject()
{
    Delete();
}
