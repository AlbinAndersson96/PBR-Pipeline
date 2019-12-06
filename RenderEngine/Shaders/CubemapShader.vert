#version 330 core
in vec3 in_Position;

out vec3 position;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    position = in_Position;  
    gl_Position =  projection * view * vec4(position, 1.0);
}