#version 430

in vec3 position;

out vec4 out_Color;
  
uniform samplerCube environmentMap;
  
void main()
{
    vec3 envColor = textureLod(environmentMap, position, 2.2).rgb;
    
    envColor = envColor / (envColor + vec3(1.0));
    envColor = pow(envColor, vec3(1.0/2.2)); 
  
    out_Color = vec4(envColor, 1.0);
}