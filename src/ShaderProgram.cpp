#pragma once
#include "ShaderProgram.h"
#include "iostream"
std::string readFileContents(const std::string& filepath)
{
    std::ifstream stream(filepath);
    std::string line;
    std::stringstream ss;
    while (getline(stream, line)) {
        ss << line << '\n';
    }
    return ss.str();
}

ShaderProgram::ShaderProgram()
{
    shaderProgram = glCreateProgram();
}

ShaderProgram::ShaderProgram(const std::string& vertex, const std::string& fragment)
{
    shaderProgram = glCreateProgram();
    shaderReady = compileShaders(vertex, fragment);
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(shaderProgram);
}

void ShaderProgram::setShader(const std::string& vertex, const std::string& fragment)
{
    shaderReady = compileShaders(vertex, fragment);
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

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return true;
}

void ShaderProgram::reloadShader()
{
    glDeleteProgram(shaderProgram);
    shaderProgram = glCreateProgram();
    compileShaders(vertexName, fragmentName);
}

void ShaderProgram::useShaderProgram() const
{
    glUseProgram(shaderProgram);
}

void ShaderProgram::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
}
void ShaderProgram::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}
void ShaderProgram::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
}