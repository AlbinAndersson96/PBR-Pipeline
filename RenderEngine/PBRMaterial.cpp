#include "PBRMaterial.h"

PBRMaterial::PBRMaterial(char *albedoPath, char *normalPath, char *metallicPath, char *roughnessPath)
{
    _pbrShader = new Shader("RenderEngine/Shaders/PBRShader.vert", "RenderEngine/Shaders/PBRShader.frag");

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
    _pbrShader->setIntUniform("albedoMap", 0);
    _pbrShader->setIntUniform("normalMap", 1);
    _pbrShader->setIntUniform("metallicMap", 2);
    _pbrShader->setIntUniform("roughnessMap", 3);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, albedoMapID);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, normalMapID);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, metallicMapID);

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, roughnessMapID);
}