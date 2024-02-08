#include "glUtils.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define GL_LOG_FILE "gl.log"
#define MAX_SHADER_LENGTH 262144

bool parseFileIntoString(const char* fileName, char* shaderString, int maxLength) {
    FILE* file = fopen (fileName, "r");
    if (!file) {
        printf("ERROR::OPEN::FILE");
        return false;
    }

    size_t cnt = fread(shaderString, 1, maxLength - 1, file);
    if ((int)cnt >= maxLength - 1) {
        printf("WARNING::FILE::TOO::BIG");
        fclose(file);
        return false;
    }
    shaderString[cnt] = 0;
    fclose(file);
    return true;
}

bool uCreateShaders(const char* fileName, GLuint* shader, GLenum type) {
    // p points to shaderSource code
    char shaderString[MAX_SHADER_LENGTH];
    parseFileIntoString(fileName, shaderString, MAX_SHADER_LENGTH);
    *shader = glCreateShader(type);
    const GLchar* p = (const GLchar*)shaderString;
    
    // link and compile shaders
    glShaderSource(*shader, 1, &p, NULL);
    glCompileShader(*shader);

    int params = -1;
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &params);
    if (GL_TRUE != params) {
        printf("ERROR::SHADER::COMPILATION");
        return false;
    }
    return true;
}

bool uCreateProgram(GLuint vert, GLuint frag, GLuint* program) {
    *program = glCreateProgram();

    glAttachShader(*program, vert);
    glAttachShader(*program, frag);
    
    glLinkProgram(*program);

    // Error check
    GLint params = -1;
    glGetProgramiv(*program, GL_LINK_STATUS, &params);
    if (GL_TRUE != params) {
        printf("ERROR::LINKING::SHADER");
        return false;
    }
    
    glDeleteShader(vert);
    glDeleteShader(frag);
    return true;
}

GLuint uCreateProgramFromFiles(const char* vertFile, const char* fragFile) {
    GLuint vert, frag, program;
    uCreateShaders(vertFile, &vert, GL_VERTEX_SHADER);
    uCreateShaders(fragFile, &frag, GL_FRAGMENT_SHADER);
    uCreateProgram(vert, frag, &program);
    return program;
}






