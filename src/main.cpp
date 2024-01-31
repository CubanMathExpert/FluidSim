#include <iostream>
#include <vector>
#include <chrono>
#include "glad.h"
#include <GLFW/glfw3.h>
#include "Particle.h"


int main(int, char**)
{
    //window size init
    int WIDTH = 640;
    int HEIGHT = 480;

    //The current window where everything will be shown
    GLFWwindow* window;

    //If glfw initialization doesn't work this will shoot an error
    if (!glfwInit())
    {
        return -1;
    }

    //Make window into the current context
    window = glfwCreateWindow(WIDTH, HEIGHT, "FluidSim", NULL, NULL);
    glfwMakeContextCurrent(window);

    //Init the package wrangler if doesn't work shoots and error
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Could't load opengl" << std::endl;
        glfwTerminate();
        return -1;
    }

    // ---------------------------------------------------
    std::vector<Particle> particles;
    //initializeParticles(particles,1, WIDTH/2.0f, HEIGHT/2.0f);


    while (!glfwWindowShouldClose(window))
    {
        //updateParticles(particles, glfwGetTime());
        // --------------
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window); 
    }
    
    glfwTerminate();
    return 0;
    
}
