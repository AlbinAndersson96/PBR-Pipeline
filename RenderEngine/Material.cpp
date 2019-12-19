#include "Material.h"

Material::Material(char *albedoPath, char *normalPath, char *metallicPath, char *roughnessPath, bool isPBR)
{
    _pbrShader = new Shader("Shaders/PBRShader.vert", "Shaders/PBRShader.frag");
    _normalShader = new Shader("Shaders/NormalShader.vert", "Shaders/NormalShader.frag");

    if(isPBR)
        _activeShader = _pbrShader;
    else
        _activeShader = _normalShader;

    LoadTGATextureSimple(albedoPath, &albedoMapID);
    LoadTGATextureSimple(normalPath, &normalMapID);
    LoadTGATextureSimple(metallicPath, &metallicMapID);
    LoadTGATextureSimple(roughnessPath, &roughnessMapID);
}

Material::~Material()
{
    //delete _pbrShader; Causes errors. Double free. Seems to be deleted somewhere else even though I can't find it :)
}

void Material::loadTextures()
{
    _activeShader->setIntUniform("albedoMap", 0);
    _activeShader->setIntUniform("normalMap", 1);
    _activeShader->setIntUniform("metallicMap", 2);
    _activeShader->setIntUniform("roughnessMap", 3);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, albedoMapID);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, normalMapID);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, metallicMapID);

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, roughnessMapID);
}

void Material::SwapShader(bool usePBR)
{
    if(usePBR)
        _activeShader = _pbrShader;
    else
        _activeShader =_normalShader;
}