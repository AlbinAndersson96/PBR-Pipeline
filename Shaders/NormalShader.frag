#version 430

in vec3 normal;
in vec2 texCoord;
in vec3 position;

uniform vec3 cameraPos;
uniform sampler2D albedoMap;
uniform sampler2D normalMap;

uniform vec3 lightColors[4];
uniform vec3 lightPositions[4];

out vec4 out_Color;

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

    vec3 lightDir = normalize(lightPositions[0] - position);

    float lambertian = max(dot(lightDir, normal), 0.2f);
    float specular = 0.0;

    if(lambertian > 0.0f);
    {
        vec3 viewDir = normalize(-position);
        vec3 halfDir = normalize(lightDir + viewDir);
        float specAngle = max(dot(halfDir, normal), 0.0f);
        specular = pow(specAngle, 10.0f);
    }
    vec3 color = albedoTex * lambertian + vec3(1.0f, 1.0f, 1.0f) * specular;

    color = vec3(min(1.0f, color.r), min(1.0f, color.g), min(1.0f, color.b));

    out_Color = vec4(color , 1.0);
} 