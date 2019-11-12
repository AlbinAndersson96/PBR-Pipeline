#include "Material.h"

Material::Material(char *texturePath)
{
    LoadTGATextureSimple(texturePath, &textureID);
}

Material::~Material()
{
    
}