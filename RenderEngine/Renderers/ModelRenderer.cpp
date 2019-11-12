#include "ModelRenderer.h"

ModelRenderer::ModelRenderer()
{
    _pbrShader = new PBRShader();
}

ModelRenderer::~ModelRenderer()
{
    delete _pbrShader;
}

void ModelRenderer::render(Camera *camera, Renderable object)
{ 
    glEnable(GL_DEPTH_TEST);

    _pbrShader->use(camera->_view, camera->_frustum, camera->_position);

    glBindVertexArray(object._VAO);

    glBindBuffer(GL_ARRAY_BUFFER, object._VBO);
    glVertexAttribPointer(glGetAttribLocation(_pbrShader->_program, "in_Position"), 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(glGetAttribLocation(_pbrShader->_program, "in_Position"));

    glBindBuffer(GL_ARRAY_BUFFER, object._NBO);
    glVertexAttribPointer(glGetAttribLocation(_pbrShader->_program, "in_Normal"), 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(glGetAttribLocation(_pbrShader->_program, "in_Normal"));

    glBindBuffer(GL_ARRAY_BUFFER, object._TBO);
    glVertexAttribPointer(glGetAttribLocation(_pbrShader->_program, "in_TexCoord"), 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(glGetAttribLocation(_pbrShader->_program, "in_TexCoord"));

    glBindTexture(GL_TEXTURE_2D, object._material.textureID);

    glDrawElements(GL_TRIANGLES, object._model->numIndices, GL_UNSIGNED_INT, 0L);
}