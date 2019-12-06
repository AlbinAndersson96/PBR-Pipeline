#include "PBRMaterial.h"

PBRMaterial::PBRMaterial(char *albedoPath, char *normalPath, char *metallicPath, char *roughnessPath, bool isPBR)
{
    _pbrShader = new Shader("RenderEngine/Shaders/PBRShader.vert", "RenderEngine/Shaders/PBRShader.frag");
    _normalShader = new Shader("RenderEngine/Shaders/NormalShader.vert", "RenderEngine/Shaders/NormalShader.frag");

    if(isPBR)
        _activeShader = _pbrShader;
    else
        _activeShader = _normalShader;

    LoadTGATextureSimple(albedoPath, &albedoMapID);
    LoadTGATextureSimple(normalPath, &normalMapID);
    LoadTGATextureSimple(metallicPath, &metallicMapID);
    LoadTGATextureSimple(roughnessPath, &roughnessMapID);
}

PBRMaterial::~PBRMaterial()
{
    //delete _pbrShader; Causes errors. Double free. Seems to be deleted somewhere else even though I can't find it :)
}

void PBRMaterial::loadTextures()
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

void PBRMaterial::SwapShader(bool usePBR)
{
    if(usePBR)
        _activeShader = _pbrShader;
    else
        _activeShader =_normalShader;
}