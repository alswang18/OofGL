#pragma once

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "glm/glm.hpp"

class ShaderProgram;
class Camera {
public:
    Camera(int width, int height, glm::vec3 position);

    // Updates the camera matrix to the Vertex Shader
    void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
    // Exports the camera matrix to a shader
    void Matrix(ShaderProgram& shader, const char* uniform);
    void Inputs(GLFWwindow* window);

    glm::vec3 Position;
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 cameraMatrix = glm::mat4(1.0f);

    int width;
    int height;

    float speed = 0.001f;
    float sensitivity = 100.0f;
    bool firstClick = true;
};