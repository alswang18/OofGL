#pragma once

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "GLFW/glfw3.h"

class ShaderProgram;
class Camera
{
    public:
        Camera(int width, int height, glm::vec3 position);

        void Matrix(float FOVdeg, float nearPlane, float farPlane, ShaderProgram& shader, const char* uniformName);
        void Inputs(GLFWwindow* window);

        glm::vec3 Position;
        glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

        int width;
        int height;

        float speed = 0.001f;
        float sensitivity = 100.0f;
        bool firstClick = true;
};