#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "glad.h"
#include <GLFW/glfw3.h>
#include <random>
#include "particle.h"

// This include works on main cause included header
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/*
    This file contains a bunch of utility functions that can be used to simplify reading the code in main.
*/

void framebuffer_size_callback(GLFWwindow* window, int width, int height); //Resize window
void processInput(GLFWwindow* window); //Actions when inputs are given to the window.
void generateCircleVertices(float radius, int segments, std::vector<float>& vertices);
void renderFPS(GLFWwindow* window);
float genRandomFloat(float min, float max);
void particleData(std::vector<Particle>& particles);
void printVec2(glm::vec2 vec);
