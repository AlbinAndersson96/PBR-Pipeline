#version 430

in vec3 normal;
in vec2 texCoord;
in vec3 position;

uniform vec3 cameraPos;
uniform sampler2D albedoMap;
uniform sampler2D normalMap;
uniform sampler2D metallicMap;
uniform sampler2D roughnessMap;

uniform samplerCube irradianceMap;
uniform samplerCube prefilterMap;
uniform sampler2D   brdfLUT;

uniform vec3 lightColors[4];
uniform vec3 lightPositions[4];

out vec4 out_Color;

const float PI = 3.14159265359;

vec3 calcBumbpedNormal(vec3 normal, vec3 bump)
{
    vec3 norm = normalize(normal);
    vec3 tangent = cross(normal, vec3(1, 2, 3));
    tangent = normalize(tangent - dot(tangent, normal) * normal);
    vec3 bitangent = cross(tangent, normal);
    bump = 2.0 * bump - vec3(1.0, 1.0, 1.0);
    vec3 newNormal;
    mat3 TBN = mat3(tangent, bitangent, normal);
    newNormal = TBN * bump;
    newNormal = normalize(newNormal);
    return newNormal;
}

void main()
{
	vec3 albedoTex = texture(albedoMap, texCoord).rgb;
	vec3 albedo     = vec3(pow(albedoTex.r, 2.2), pow(albedoTex.g, 2.2), pow(albedoTex.b, 2.2));
    vec3 bumpNormal = calcBumbpedNormal(normal, texture(normalMap, texCoord).rgb);   
    float metallic  = texture(metallicMap, texCoord).r;


    float illumination = 0.0f;
    for(int i = 0; i < 4; ++i) 
    {
        vec3 L = lightPositions[i] - position;

        illumination = max(0.2f, dot(L, bumpNormal));
    }   

    vec3 diffuse = illumination * albedo;

    out_Color = vec4(albedo , 1.0);
} 