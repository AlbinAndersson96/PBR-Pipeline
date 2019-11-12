#version 430

in vec3 normal;
in vec2 texCoord;
in vec3 position;

uniform vec3 cameraPos;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform sampler2D textureSampler;

out vec4 out_Color;

void main()
{
	vec3 lightDir = vec3(1.0f, 0.0f, 0.0f);
	vec3 lightCol = vec3(1.0f, 1.0f, 1.0f);

	vec3 diffuse = dot(normal, lightDir) * lightCol;

	vec3 viewDir = normalize(cameraPos-position);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
	vec3 specular = 0.7f * spec * lightCol;

	vec3 light = diffuse + specular;
	light = vec3(max(0.2f, light.x), max(0.2f, light.y), max(0.2f, light.z));

	out_Color = vec4(light, 1.0) * texture(textureSampler, texCoord);
} 