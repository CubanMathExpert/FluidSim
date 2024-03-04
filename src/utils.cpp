#include "utils.h"

const char* readShaderFile(std::string filePath)
{
    std::ifstream file;
    file.open(filePath, std::ios::in);
    // If file doesn't open return nullptr and send error msg
    if (!file)
    {
        std::cout << "ERROR::OPENING::FILE" << std::endl;
        return nullptr;
    }
    // If file opens append lines and \n in result (while getline will iterate over the lines of the file)
    else
    {
        std::cout << "SUCCESS::CREATING::FILE" << std::endl;
        std::string result = "";
        std::string line;
        while (getline(file, line))
        {
            result.append(line);
            result.append("\n");
        }
        file.close();
        /*
            After many bugs I found that c_str() cause the pointer to go out of scope
            and it would return some type of nullptr. So when I create the copy with strlen + 1 it works and keeps
            the value. So when you return you still have the value in it and not nullptr. 
            (Shity explanation but I'm just glad it works)
        */
        const char* cstrResult = result.c_str();
        char* copy = new char[strlen(cstrResult) + 1];
        strcpy(copy, cstrResult);
        return copy;  // turns the string into a const char*
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // Close window when pressing escape
        glfwSetWindowShouldClose(window, true);
}






