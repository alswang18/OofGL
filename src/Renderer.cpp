#pragma once
#include "Renderer.h"
#include "ShaderProgram.h"

#include "Camera.h"
#include "ElementBufferObject.h"
#include "Texture.h"
#include "Timer.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "glad/glad.h"
#include "imgui.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#ifdef _WIN32
#include <Windows.h>
#endif

#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif

#ifdef GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#endif

// settings
const uint32_t SCR_WIDTH = 800;
const uint32_t SCR_HEIGHT = 600;

// Vertices coordinates
GLfloat vertices[] = { //     COORDINATES     /        COLORS      /   TexCoord  //
    -0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
    -0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f,
    0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
    0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f,
    0.0f, 0.8f, 0.0f, 0.92f, 0.86f, 0.76f, 2.5f, 5.0f
};

// Indices for vertices order
GLuint indices[] = {
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
};

int main()
{
#ifdef _WIN32
#ifdef _MSC_VER
#if PRODUCTION_BUILD == 0
    // This stuff allows for a printf console in a non-console windows app.
    AllocConsole();
    (void)freopen("conin$", "r", stdin);
    (void)freopen("conout$", "w", stdout);
    (void)freopen("conout$", "w", stderr);
    std::cout.sync_with_stdio();
#endif
#endif
#endif

    if (!initalizeGlFW()) {
        std::printf("Failed to initalize GLFW.\n");
        return -1;
    }

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OofGL", NULL, NULL);
    if (window == NULL) {
        std::printf("Failed to create GLFW window.\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // This needs to happen after glfw sets the current context window.
    if (!loadGlad()) {
        std::printf("Failed to initalize GLAD.\n");
        return -1;
    }

    VertexArrayObject VAO;
    VAO.Bind();

    VertexBufferObject VBO(vertices, sizeof(vertices));

    ElementBufferObject EBO(indices, sizeof(indices));

    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    // load and create a texture
    // -------------------------
    Texture texture(RESOURCES_PATH "/images/wall.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);

    ShaderProgram shader("vertex.glsl", "fragment.glsl");
    if (!shader.isShaderReady()) {
        std::printf("Failed to compile shaders.\n");
        return -1;
    }

    texture.texUnit(shader, "tex0", 0);
    shader.use();
    imguiInit(window);

    // Enables a depth buffer.
    glEnable(GL_DEPTH_TEST);

    // Creates camera object
    Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

    Timer timer;
    int indexCount = sizeof(indices) / sizeof(int);
    glm::mat4 model = glm::mat4(1.0f);
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {
        // input
        // -----
        processInput(window, shader);
        imguiStartFrame();
        shader.use();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        texture.Bind();
        shader.use();

        // Handles camera inputs
        camera.Inputs(window);
        // Updates and exports the camera matrix to the Vertex Shader
        camera.Matrix(45.0f, 0.1f, 100.0f, shader, "camMatrix");

        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 proj = glm::mat4(1.0f);

        model = glm::rotate(model, glm::radians(0.1f), glm::vec3(0.0f, 1.0f, 0.0f));

        view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
        proj = glm::perspective(glm::radians(45.0f), static_cast<float>(SCR_WIDTH / SCR_HEIGHT), 0.1f, 100.0f);

        int modelLocation = glGetUniformLocation(shader.getShaderId(), "model");
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

        int viewLocation = glGetUniformLocation(shader.getShaderId(), "view");
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

        int projLocation = glGetUniformLocation(shader.getShaderId(), "proj");
        glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(proj));

        VAO.Bind();
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

        imguiDraw(timer, shader);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    imguiTerminate();
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void imguiInit(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 430");
}

void imguiTerminate()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void imguiStartFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void imguiDraw(Timer& timer, ShaderProgram& shader)
{
    ImGui::Begin("ImGui Panel Window");
    ImGui::Text("Time elapsed %.3f ms", timer.ElapsedMillis());
    if (ImGui::Button("Reload Shader")) {
        shader.reloadShader();
        if (!shader.isShaderReady()) {
            std::printf("Failed to compile shaders.\n");
        }
    }
    timer.Reset();
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool initalizeGlFW()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    return true;
}

bool loadGlad()
{
    // glad: load all OpenGL function pointers
    // ---------------------------------------

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    return true;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window, ShaderProgram& program)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}