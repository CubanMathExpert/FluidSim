#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "glad.h"
#include <GLFW/glfw3.h>

void compileErrorCheck(unsigned int shader);
void programErrorCheck(unsigned int program);


int main(int, char**)
{
    int WIDTH = 640;//window size init
    int HEIGHT = 480;
    GLFWwindow* window; //The current window
    
    if (!glfwInit()) //If glfw initialization doesn't work this will shoot an error
    {
        return -1;
    }
    
    window = glfwCreateWindow(WIDTH, HEIGHT, "FluidSim", NULL, NULL); //Make window into the current context
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) //Init the package wrangler if doesn't work shoots and error
    {
        std::cout << "Could't load opengl" << std::endl;
        glfwTerminate();
        return -1;
    }
    // ---------------------------------------------------
    
    float vertices[] = {   
        -0.5f, -0.5, 0.0f,
        0.5f, -0.5, 0.0f,
        0.5f, 0.5, 0.0f
    };


    //----------------------------------------------------
    while (!glfwWindowShouldClose(window))
    {
        
        //---------- RENDER
        glClearColor(0.5f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // ------------
        glfwPollEvents();
        glfwSwapBuffers(window); 
    }
    
    glfwTerminate();
    return 0;
    
}



