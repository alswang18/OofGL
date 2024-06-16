#pragma once
#include <GLFW/glfw3.h>

class ShaderProgram;
class Timer;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, ShaderProgram& program);

bool initalizeGlFW();
bool loadGlad();
void imguiInit(GLFWwindow* window);
void imguiTerminate();
void imguiStartFrame();
void imguiDraw(Timer& timer, ShaderProgram& shader);