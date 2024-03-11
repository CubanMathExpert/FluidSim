#include "glad.h"
#include <GLFW/glfw3.h>
#include "shader_c.h"
#include "utils.h"
#include <iostream>
#include <vector>

// there is more but most of the useful stuff in here

const glm::vec3 gravity = glm::vec3(0.0f, -9.81f, 0.0f);
#define PI 3.141592653589793f

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "FLuidSim", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    Shader ourShader("../shaders/vertexShader.glsl", "../shaders/fragmentShader.glsl"); // you can name your shader files however you like

    // set up vertex data (and buffer(s)) and configure vertex attributes

    // particle data
    const float particleRadius = 0.05f;
    const int particleSegments = 20;
    std::vector<float> vertices;
    generateCircleVertices(particleRadius, particleSegments, vertices);

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);

    float lastFrame = glfwGetTime();
    glm::vec3 particlePosition(0.0f, 2.9f, 0.0f);
    glm::vec3 particleVelocity(0.0f); // initial velocity
    // render loop
    while (!glfwWindowShouldClose(window))
    {

        // time and particle movement
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        particleVelocity += gravity * deltaTime;
        particlePosition += particleVelocity * deltaTime;

        if (particlePosition.x < -0.0f || particlePosition.x > SCR_WIDTH)
        {
            particleVelocity.x *= -1.0f; // invert x velo
        }
        if (particlePosition.y < (-3.0f + particleRadius) || particlePosition.y > (3.0 - particleRadius))
        {
            particleVelocity.y *= -1.0f; // invert x velo
        }

        // input
        processInput(window);

        // render-----------------------------------------------------------------------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // create transforms------------------------------------------------------------

        // projection matrix (2D no need for model or view)
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f, -1.0f, 1.0f);
        // shader and bind VAO's ---------------------------------------------------------

        ourShader.use();

        glBindVertexArray(VAO);

        // send uniforms to vertex shader-------------------------------------------------
        glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniform3fv(glGetUniformLocation(ourShader.ID, "offset"), 1, &particlePosition[0]);
        //---------------------------------------------------------------------------

        glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 3);
        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}


