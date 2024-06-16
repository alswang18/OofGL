#include "VertexBufferObject.h"

VertexBufferObject::VertexBufferObject(GLfloat* vertices, GLsizeiptr size)
{
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VertexBufferObject::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBufferObject::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::Delete()
{
    glDeleteBuffers(1, &id);
}

VertexBufferObject::~VertexBufferObject()
{
    Delete();
}