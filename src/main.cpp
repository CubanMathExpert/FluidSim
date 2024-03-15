#include "glad.h"
#include <GLFW/glfw3.h>
#include "shader_c.h"
#include "../inc/particle.h"
#include "utils.h"
#include <iostream>
#include <vector>

// there is more but most of the useful stuff in here



// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const int num_particles = 10;

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

    // particle data
    Particle particle;
    std::vector<float> vertices;
    generateCircleVertices(particle.radius, particle.segments, vertices);

    // http://www.opengl-tutorial.org/intermediate-tutorials/billboards-particles/particles-instancing/
    unsigned int particle_vertex_buffer;
    glGenBuffers(1, &particle_vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, particle_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()* sizeof(float), vertices.data(), GL_STATIC_DRAW);

    unsigned int  VAO;
    glGenVertexArrays(1, &VAO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    
    float lastFrame = 0.0f;
    
    particle.position = glm::vec3(0.0f, 2.9f, 0.0f);
    particle.velocity = glm::vec3(7.0f, 0.0f, 0.0f); // initial velocity

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // time and particle movement
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // particle handlers
        updateParticles(particle, deltaTime);
        checkEdgeCollisions(particle, deltaTime);

        // input
        processInput(window);

        // render-----------------------------------------------------------------------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // create transforms------------------------------------------------------------

        // projection matrix (2D no need for model or view)
        glm::mat4 projection = glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f, -1.0f, 1.0f);
        // shader and bind VAO's ---------------------------------------------------------

        ourShader.use();

        // send uniforms to vertex shader-------------------------------------------------
        glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniform3fv(glGetUniformLocation(ourShader.ID, "offset"), 1, &particle.position[0]);
        glUniform1f(glGetUniformLocation(ourShader.ID, "deltaTime"), deltaTime);
        //---------------------------------------------------------------------------

        glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 3);
        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        renderFPS(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}


