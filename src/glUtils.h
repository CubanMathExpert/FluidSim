#include "glad.h"
#include <GLFW/glfw3.h>
#include <stdarg.h>

#define GL_LOG_FILE "gl.log"


bool uCreateShaders(const char* fileName, GLuint* shader, GLenum type);
bool parseFileIntoString(const char* fileName, char* shaderString, int maxLength);
bool uCreateProgram(GLuint vert, GLuint frag, GLuint* program);
GLuint uCreateProgramFromFiles(const char* vertFile, const char* fragFile);








