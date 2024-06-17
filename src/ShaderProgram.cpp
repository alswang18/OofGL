#pragma once
#include "ShaderProgram.h"
#include "iostream"
#include <fstream>
#include <sstream>

// Reads a text file and outputs a string with everything in the text file
std::string readFileContents(const std::string& filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (in) {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return (contents);
    }
    throw(errno);
}

ShaderProgram::ShaderProgram()
{
    shaderId = glCreateProgram();
}

ShaderProgram::ShaderProgram(const std::string& vertexFilename, const std::string& fragmentFilename)
{
    shaderId = glCreateProgram();
    shaderReady = compileShaders(vertexFilename, fragmentFilename);
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(shaderId);
}

bool ShaderProgram::compileShaders(const std::string& vertex, const std::string& fragment)
{
    vertexName = vertex;
    std::string vertexPath = RESOURCES_PATH "shaders/" + vertex;
    std::string vertexShaderString = readFileContents(vertexPath);

    const char* vertexShaderSource = vertexShaderString.c_str();
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        return false;
    }
    fragmentName = fragment;
    std::string fragmentPath = RESOURCES_PATH "shaders/" + fragment;
    std::string fragmentShaderString = readFileContents(fragmentPath);

    const char* fragmentShaderSource = fragmentShaderString.c_str();
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        return false;
    }

    glAttachShader(shaderId, vertexShader);
    glAttachShader(shaderId, fragmentShader);
    glLinkProgram(shaderId);

    glGetProgramiv(shaderId, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderId, 512, NULL, infoLog);
        return false;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return true;
}

void ShaderProgram::reloadShader()
{
    glDeleteProgram(shaderId);
    shaderId = glCreateProgram();
    shaderReady =compileShaders(vertexName, fragmentName);
}

void ShaderProgram::use() const
{
    glUseProgram(shaderId);
}

void ShaderProgram::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(shaderId, name.c_str()), (int)value);
}
void ShaderProgram::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(shaderId, name.c_str()), value);
}
void ShaderProgram::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(shaderId, name.c_str()), value);
}