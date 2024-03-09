#include "utils.h"

#define PI 3.141592653589793f

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









