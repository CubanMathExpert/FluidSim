#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 offset;

void main()
{
    vec3 offsetPosition = aPos + offset;

    gl_Position = projection * vec4(offsetPosition, 1.0);
} 