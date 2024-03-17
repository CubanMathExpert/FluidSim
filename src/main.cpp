#include "glad.h"
#include <GLFW/glfw3.h>
#include "shader_c.h"
#include "particle.h"
#include "utils.h"
#include <iostream>
#include <vector>

// there is more but most of the useful stuff in here



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

    // generate list of particle locations/translation-vectors
    const int num_particles = 1000;
    glm::vec2 translations[num_particles];
    glm::vec2 velocities[num_particles];
    /*
        MAKE THE INITIAL VELOCITIES WITH RANDOM FLOAT

    */
    for (int i = 0; i < num_particles; i++)
    {
            glm::vec2 translation;
            translation.x = randomFloat(4.0f, 8);
            translation.y = randomFloat(3.0f, 6);
            translations[i] = translation;
    }
    

    // Buffer for instance data (I guess we put all the information for the N particles)
    unsigned int positionsVBO;
    glGenBuffers(1, &positionsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * num_particles, &translations[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // buffer for initial velocities
    unsigned int velocitiesVBO;
    glGenBuffers(1, &velocitiesVBO);
    glBindBuffer(GL_ARRAY_BUFFER, velocitiesVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * num_particles, &velocities[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    // particle vertices data
    Particle particle;
    std::vector<float> vertices;
    generateCircleVertices(particle.radius, particle.segments, vertices);

    // data for one circle
    unsigned int particle_vertex_buffer, VAO;
    glGenBuffers(1, &particle_vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, particle_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()* sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // set instance data
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, positionsVBO); // this attribute comes from a different vertex buffer
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(1, 1);

    float lastFrame = 0.0f;
    
    particle.position = glm::vec2(0.0f, 2.9f);
    particle.velocity = glm::vec2(7.0f, 0.0f); // initial velocity

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // time 
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // generate particle data

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
        glUniform3fv(glGetUniformLocation(ourShader.ID, "offset"), 1, &particle.position[0]); // this is being updated and send to the GPU when I use update functino
        glUniform1f(glGetUniformLocation(ourShader.ID, "deltaTime"), deltaTime);
        // set array of offsets
        for (unsigned int i = 0; i < num_particles; i++)
        {
            ourShader.setVec2(("offsets[" + std::to_string(i) + "]"), translations[i]);
        }
        //---------------------------------------------------------------------------
        glBindVertexArray(VAO);
        glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, vertices.size() / 3, num_particles);
        //glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 3);
        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        renderFPS(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &particle_vertex_buffer);
    glDeleteBuffers(1, &positionsVBO);
    glDeleteBuffers(1, &velocitiesVBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}


