#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "glad.h"
#include <GLFW/glfw3.h>

/*
    This file contains a bunch of utility functions that can be used to simplify reading the code in main.
*/

const char* readShaderFile(std::string filePath); //Read shader files
void framebuffer_size_callback(GLFWwindow* window, int width, int height); //Resize window
void processInput(GLFWwindow* window); //Actions when inputs are given to the window.
void printHex(const char* str);
void printChar(const char* str);
