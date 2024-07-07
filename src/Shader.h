#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <cerrno>
#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <string>
#include <glm/glm.hpp>
std::string get_file_contents(const char* filename);

class Shader {
public:
    // Reference ID of the Shader Program
    GLuint ID;
    // Constructor that build the Shader Program from 2 different shaders
    Shader(const char* vertexFile, const char* fragmentFile);
    ~Shader();

    // Activates the Shader Program
    void Activate();
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec2(const std::string& name, glm::vec2 value) const;
    void setVec3(const std::string& name, glm::vec3 value) const;
    void setVec4(const std::string& name, glm::vec4 value) const;
    void setMat4(const std::string& name, glm::mat4 value) const;

private:
    // Checks if the different Shaders have compiled properly
    void compileErrors(unsigned int shader, const char* type);
    // Deletes the Shader Program
    void Delete();
};

#endif