#include "ModelRenderer.h"

ModelRenderer::ModelRenderer()
{
}

ModelRenderer::~ModelRenderer()
{
}

void ModelRenderer::render(Camera *camera, Renderable object, PointLight *pointLights, int nrOfLights, Cubemap cubemap)
{ 
    glEnable(GL_DEPTH_TEST);
    
    glBindVertexArray(object._VAO);

    object._material._activeShader->use();

    object._material._activeShader->setMat4Uniform("viewMatrix", camera->_view);
    object._material._activeShader->setMat4Uniform("projectionMatrix", camera->_frustum);

    object._material._activeShader->setVec3Uniform("cameraPos", camera->_position, 1);
    object._material._activeShader->setVec3Uniform("lightPositions", *(&pointLights[0]._position), nrOfLights);
    object._material._activeShader->setVec3Uniform("lightColors", *(&pointLights[0]._color), nrOfLights);

    object._material.loadTextures();

    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap._convolutedTexture);
    object._material._activeShader->setIntUniform("irradianceMap", 4);

    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap._mipmapTexture);
    object._material._activeShader->setIntUniform("prefilterMap", 5);

    glActiveTexture(GL_TEXTURE6);
    glBindTexture(GL_TEXTURE_2D, cubemap._brdfConvolutedTexture);
    object._material._activeShader->setIntUniform("brdfLUT", 6);

    glDrawElements(GL_TRIANGLES, object._model->numIndices, GL_UNSIGNED_INT, 0L);
}