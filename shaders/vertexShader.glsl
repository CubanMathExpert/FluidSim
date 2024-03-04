#version 330 core
layout (location = 0) in vec3 aPos; // The position variable has attribute position 0

out vec4 vertexColor; // Specifie a color output to the fragment shader

void main() {
    gl_position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}