#version 430

in vec3 in_Position;
in vec3 in_Normal;
in vec2 in_TexCoord;

uniform vec3 lightPos[4];
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform sampler2D normalMap;

out vec2 texCoord;
out vec3 position;
out vec3 normal;
out vec3 lightPositions[4];

void main()
{
    gl_Position = projectionMatrix * viewMatrix * vec4(in_Position, 1.0);
    position = in_Position;
    texCoord = in_TexCoord;
    normal = in_Normal;//texture(normalMap, texCoord).rgb * 2.0 - 1.0 ;

    for(int i = 0; i<4; i++)
    {
        //lightPositions[i] = vec3(viewMatrix) * lightPos[i];
        lightPositions[i] = lightPos[i];
    }
}