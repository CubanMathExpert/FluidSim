#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0

uniform mat4 projection;
uniform vec3 offset;
uniform float deltaTime;
uniform vec2 offsets[10];

void main()
{
    vec3 offsetPosition = aPos + offset;

    vec2 offset = offsets[gl_InstanceID];
    gl_Position = projection * vec4(aPos + offsetPosition, 1.0);
} 