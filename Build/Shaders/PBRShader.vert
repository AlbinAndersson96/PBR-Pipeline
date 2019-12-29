#version 430
in vec3 in_Position;
in vec2 in_TexCoord;
in vec3 in_Normal;

out vec2 texCoord;
out vec3 position;
out vec3 normal;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main()
{
    texCoord = in_TexCoord;
    position = vec3(vec4(in_Position, 1.0));
    normal = in_Normal;   

    gl_Position =  projectionMatrix * viewMatrix * vec4(position, 1.0);
}