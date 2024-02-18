#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "glad.h"
#include <GLFW/glfw3.h>
#include "gl_utils"

void compileErrorCheck(unsigned int shader);
void programErrorCheck(unsigned int program);


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
    // declare vertices and create VBO + store data in GPU Memory
    float vertices[] = {
        -0.5f, -0.5, 0.0f,
        0.5f, -0.5, 0.0f,
        0.5f, 0.5, 0.0f
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint shaderProgram = uCreateProgramFromFiles("vertexShader.vert", "fragmentShader.frag");
    
    //Compile Shaders and link in program    
    //vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);


    //glShaderSource(vertexShader, 1, &vertexSource, NULL);
    //glCompileShader(vertexShader);
    //compileErrorCheck(vertexShader);

    //glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    //glCompileShader(fragmentShader);
    //compileErrorCheck(fragmentShader);

    //shaderProgram = glCreateProgram();
    //glAttachShader(shaderProgram, vertexShader);
    //glAttachShader(shaderProgram, fragmentShader);
    //glLinkProgram(shaderProgram);
    //programErrorCheck(shaderProgram);

    //glDeleteShader(vertexShader);
    //glDeleteShader(fragmentShader);

    // Link vertex attributes : how openGL interprets vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    //----------------------------------------------------
    while (!glfwWindowShouldClose(window))
    {
        
        // --------------
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window); 
    }
    
    glfwTerminate();
    return 0;
    
}

void compileErrorCheck(unsigned int shader) {
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void programErrorCheck(unsigned int program) {
    int success;
    char infoLog[512];
    glGetShaderiv(program, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }   
}



