#include "Texture.h"
#include "stb_image/stb_image.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
    type = texType;

    glGenTextures(1, &id);
    glActiveTexture(slot);
    glBindTexture(type, id);

    // Set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load and generate the texture
    int width, height, numberOfColorChannels;
    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load(image, &width, &height, &numberOfColorChannels, 0);
    if (data) {
        glTexImage2D(type, 0, format, width, height, 0, format, pixelType, data);
        glGenerateMipmap(type);
    } else {
        std::printf("Failed to load texture\n");
    }
    stbi_image_free(data);
    glBindTexture(type, 0);
}

void Texture::texUnit(ShaderProgram& shader, const char* uniform, GLuint unit)
{
    GLuint texUni = glGetUniformLocation(shader.getShaderProgram(), uniform);
    shader.useShaderProgram();
    // This is the index of the texture unit.
    glUniform1i(texUni, unit);
}

void Texture::Bind()
{
    glBindTexture(type, id);
}

void Texture::Unbind()
{
    glBindTexture(type, 0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &id);
}

Texture::~Texture()
{
    Delete();
}