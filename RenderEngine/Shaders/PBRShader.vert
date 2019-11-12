#version 430

in vec3 in_Position;
in vec3 in_Normal;
in vec2 in_TexCoord;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 normal;
out vec2 texCoord;
out vec3 position;

void main()
{
    gl_Position = projectionMatrix * viewMatrix * vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);
    position = in_Position;
    normal = in_Normal;
    texCoord = in_TexCoord;
}