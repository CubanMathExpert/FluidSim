#include "utils.h"

#define PI 3.141592653589793f
// Global variables for FPS calculation
float deltaTime = 0.0f;
float lastFrame = 0.0f;
int frameCount = 0;
float fps = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // Close window when pressing escape
        glfwSetWindowShouldClose(window, true);
}

void generateCircleVertices(float radius, int segments, std::vector<float>& vertices)
{
    for (int i = 0; i < segments; ++i)
    {
        float angle = 2.0f * PI * i / segments;
        float x = radius * glm::cos(angle);
        float y = radius * glm::sin(angle);
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(0.0f);
    }
}

void renderFPS(GLFWwindow* window)
{
    float currentFrame = glfwGetTime();
    deltaTime += currentFrame - lastFrame;
    lastFrame = currentFrame;
    frameCount++;
    if (deltaTime >= 1.0f)
    {
        fps = frameCount / deltaTime;
        frameCount = 0;
        deltaTime = 0;
    }

    // render FPS text
    std::string fpsString = "FluidSim/FPS: " + std::to_string(static_cast<int>(std::round(fps)));
    glfwSetWindowTitle(window, fpsString.c_str());
}








