#include "Model.h"
#include "Timer.h"
#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif
#ifdef _WIN32
#include <Windows.h>
#endif
const std::string texPath = std::string(RESOURCES_PATH) + "/images/";
const std::string shaderPath = std::string(RESOURCES_PATH) + "/shaders/";
const std::string modelPath = std::string(RESOURCES_PATH) + "/models/";

const unsigned int width = 800;
const unsigned int height = 800;

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
    // Initialize GLFW
    glfwInit();

    // Tell GLFW what version of OpenGL we are using
    // In this case we are using OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Tell GLFW we are using the CORE profile
    // So that means we only have the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
    GLFWwindow* window = glfwCreateWindow(width, height, "OofGL", NULL, NULL);
    // Error check if the window fails to create
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Introduce the window into the current context
    glfwMakeContextCurrent(window);

    // Load GLAD so it configures OpenGL
    gladLoadGL();
    // Specify the viewport of OpenGL in the Window
    // In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
    glViewport(0, 0, width, height);

    // Generates Shader object using shaders default.vert and default.frag
    Shader shaderProgram((shaderPath + "default.vert").c_str(), (shaderPath + "default.frag").c_str());

    // Take care of all the light related things
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    shaderProgram.Activate();
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    // Enables the Depth Buffer
    glEnable(GL_DEPTH_TEST);

    // Creates camera object
    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    /*
     * I'm doing this relative path thing in order to centralize all the resources into one folder and not
     * duplicate them between tutorial folders. You can just copy paste the resources from the 'Resources'
     * folder and then give a relative path from this folder to whatever resource you want to get to.
     * Also note that this requires C++17, so go to Project Properties, C/C++, Language, and select C++17
     */

    // Load in a model
    Model model((modelPath + "bunny/scene.gltf").c_str());

    // Original code from the tutorial
    // Model model("models/bunny/scene.gltf");

    double prevTime = 0.0;
    double crntTime = 0.0;
    double timeDiff = 0.0;
    // Keeps track of the amount of frames in timeDiff
    unsigned int counter = 0;
    // Enable VSync
    glfwSwapInterval(1);
    // Main while loop
    while (!glfwWindowShouldClose(window)) {

        // Updates counter and times
        crntTime = glfwGetTime();
        timeDiff = crntTime - prevTime;
        counter++;

        if (timeDiff >= 1.0 / 30.0) {
            // Creates new title
            std::string FPS = std::to_string((1.0 / timeDiff) * counter);
            std::string ms = std::to_string((timeDiff / counter) * 1000);
            std::string newTitle = "FPS - " + FPS + "FPS / " + ms + "ms";
            glfwSetWindowTitle(window, newTitle.c_str());

            // Resets times and counter
            prevTime = crntTime;
            counter = 0;

            // Use this if you have disabled VSync
            camera.Inputs(window);
        }
        // Specify the color of the background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clean the back buffer and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Updates and exports the camera matrix to the Vertex Shader
        camera.updateMatrix(45.0f, 0.1f, 100.0f);

        // Draw a model
        model.Draw(shaderProgram, camera);

        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);
        // Take care of all GLFW events
        glfwPollEvents();
    }

    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program
    glfwTerminate();
    return 0;
}