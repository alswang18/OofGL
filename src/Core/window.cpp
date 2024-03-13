#include "window.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <sstream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "fmt/core.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#define ASSERT(x) \
    if (!(x))     \
        __debugbreak();

#define GLCall(x)                                  \
    do                                             \
    {                                              \
        GLClearError();                            \
        x;                                         \
        ASSERT(GLLogCall(#x, __FILE__, __LINE__)); \
    } while (0)

static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR)
    {
        std::cout << "GLClearError" << std::endl;
    }
}

static bool GLLogCall(const char *function, const char *file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << std::hex << error << std::dec << ")" << function << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// function that turns file into a string

// function that compiles shader
static unsigned int compileShader(unsigned int type, const std::string &file_content)
{
    unsigned int id = glCreateShader(type);
    const char *src = file_content.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));
    return id;
}
static std::string readFile(const char *filepath)
{
    {
        // check if file exists
        if (std::filesystem::exists(filepath))
        {
            std::ifstream file(filepath);
            if (!file.is_open())
            {
                std::cout << "Could not open file " << filepath << std::endl;
                return "";
            }
            std::stringstream ss;
            std::string line;
            while (std::getline(file, line))
            {
                ss << line << '\n';
            }
            file.close();
            return ss.str();
        }
        else
        {
            std::cout << "File " << filepath << " does not exist" << std::endl;
            return "";
        }
    };
}

static unsigned int createShaderProgram(const std::string &vertexShaderSource, const std::string &fragmentShaderSource)
{
    int success;
    char infoLog[512];

    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);

    GLCall(glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success));

    if (!success)
    {
        GLCall(glGetShaderInfoLog(vertexShader, 512, NULL, infoLog));
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        return -1;
    }

    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    GLCall(glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success));

    if (!success)
    {
        GLCall(glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog));
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        return -1;
    }

    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    GLCall(glAttachShader(shaderProgram, vertexShader));
    GLCall(glAttachShader(shaderProgram, fragmentShader));
    GLCall(glLinkProgram(shaderProgram));
    // check for linking errors
    GLCall(glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success));
    if (!success)
    {
        GLCall(glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog));
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}

static std::string glResourceTypeToString(int resourceType)
{
    switch (resourceType)
    {
    case GL_VERTEX_SHADER:
        return "GL_VERTEX_SHADER";
    case GL_FRAGMENT_SHADER:
        return "GL_FRAGMENT_SHADER";
    case GL_GEOMETRY_SHADER:
        return "GL_GEOMETRY_SHADER";
    case GL_TESS_CONTROL_SHADER:
        return "GL_TESS_CONTROL_SHADER";
    case GL_TESS_EVALUATION_SHADER:
        return "GL_TESS_EVALUATION_SHADER";
    case GL_COMPUTE_SHADER:
        return "GL_COMPUTE_SHADER";
    default:
        return "UNKNOWN";
    }
}

int OofGLInit()
{
    float positions[6] = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.0f, 0.5f};

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers, we can't do error checking before this
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    const std::string vertexShaderPath = fmt::format("{}/{}", SHADER_PATH, "vertex.glsl");
    const std::string vertexShaderSource = readFile(vertexShaderPath.c_str());
    if (vertexShaderSource == "")
    {
        std::cout << "Failed to read vertex shader file" << std::endl;
        return -1;
    }
    const std::string fragmentShaderPath = fmt::format("{}/{}", SHADER_PATH, "fragment.glsl");
    const std::string fragmentShaderSource = readFile(fragmentShaderPath.c_str());
    if (fragmentShaderSource == "")
    {
        std::cout << "Failed to read fragment shader file" << std::endl;
        return -1;
    }

    unsigned int shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);

    if (shaderProgram == -1)
    {
        std::cout << "Failed to create shader program" << std::endl;
        return -1;
    }

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
        0.5f, -0.5f, 0.0f,  // right
        0.0f, 0.5f, 0.0f    // top
    };

    unsigned int VBO, VAO;
    GLCall(glGenVertexArrays(1, &VAO));
    GLCall(glGenBuffers(1, &VBO));
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    GLCall(glBindVertexArray(VAO));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void *>(0)));
    GLCall(glEnableVertexAttribArray(0));

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    GLCall(glBindVertexArray(0));

    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        // draw our first triangle
        GLCall(glUseProgram(shaderProgram));
        GLCall(glBindVertexArray(VAO)); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));
        GLCall(glBindVertexArray(0)); // no need to unbind it every time

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        GLCall(glfwSwapBuffers(window));
        GLCall(glfwPollEvents());
    }

    std::cout << "Closing Window" << std::endl;

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    GLCall(glDeleteVertexArrays(1, &VAO));
    GLCall(glDeleteBuffers(1, &VBO));
    GLCall(glDeleteProgram(shaderProgram));

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        GLCall(glfwSetWindowShouldClose(window, true));
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    GLCall(glViewport(0, 0, width, height));
}