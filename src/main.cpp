#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "glad.h"
#include <GLFW/glfw3.h>
#include "utils.h"

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Resize window by calling function 2nd arg
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) //Init the package wrangler if doesn't work shoots and error
    {
        std::cout << "Could't load opengl" << std::endl;
        glfwTerminate();
        return -1;
    }
    glViewport(0,0, WIDTH, HEIGHT);
    // ---------------------------------------------------
    
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    }; 
    unsigned int indices[] = {
        0,1,3
    };
    
    // Make shaders
    const char* vertSource = readShaderFile("../shaders/vertexShader.glsl");
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertSource, NULL);
    glCompileShader(vertexShader);

    const char* fragSource = readShaderFile("../shaders/fragmentShader.glsl");
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragSource, NULL);
    glCompileShader(fragmentShader);

    // WTF IS GOING ON HERE THESE TWO LOOK IDENTICAL BUT THEY AINT
    std::cout << fragSource << std::endl;
    std::cout << fragmentShaderSource << std::endl;
    if (strcmp(fragSource, fragmentShaderSource) == 0)
    {
        std::cout << "these mf are the same" << std::endl;
    }
    else
    {
        std::cout << "different" << std::endl;
    }

    // Make the program and bind the shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // VERTEX DATA
    unsigned int VBO, VAO, EBO; // From what I understand it's like train that takes the vertex data into the vertex shader
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //----------------------------------------------------
    while (!glfwWindowShouldClose(window))
    {
        //----------INPUTS
        processInput(window);
        
        //---------- RENDER
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // In case we use multiple VAO we bind it everytime
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // ------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
    
}



