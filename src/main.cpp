#include "glad.h"
#include <GLFW/glfw3.h>
#include "shader_c.h"
#include "particle.h"
#include "utils.h"


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

    // for multiple particles
    std::vector<Particle> particles(num_particles); // vector to hold all the particles
    std::vector<float> vertices;
    generateCircleVertices(particles[0].radius, particles[0].segments, vertices);

    for (int i = 0; i < num_particles; ++i)
    {
        // generate initial position and velocity
        particles[i].position = glm::vec2(-2.5f - genRandomFloat(0.0, 1.0), 1.5f + genRandomFloat(0.0, 1.0));
        particles[i].velocity = glm::vec2(genRandomFloat(3.0f, 7.0f), 0.0f); // min speed has to be 2/sqrt(2) for it to be out of spawn zone before in one second
    }
    // initial velo and positions are properly initialized

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

    
    

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // time 
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;


        // handle particle movement
        update_simulation(particles, deltaTime);
        
        // input
        processInput(window);

        // render-----------------------------------------------------------------------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.use();

        glm::mat4 projection = glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f, -1.0f, 1.0f); // orthgraphic projection screen dim 4x3
        glm::mat4 view = glm::mat4(1.0f); // camera stays at the same spot
        
        // same view and proj matrix for all particles
        glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));

        glBindVertexArray(VAO);
        for (Particle particle: particles)
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(particle.position, 0.0f));
            glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 3);
        }
        
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


