#include "Renderable.h"

Renderable::Renderable(char *modelPath,  Material material, Tag tag)
:_material(material)
,_tag(tag)
{
    _model = LoadModelPlus(modelPath);

    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);

    glGenBuffers(1, &_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, 3 * _model->numVertices * sizeof(GLfloat), _model->vertexArray, GL_STATIC_DRAW);
    glVertexAttribPointer(glGetAttribLocation(material._activeShader->_program, "in_Position"), 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(glGetAttribLocation(material._activeShader->_program, "in_Position"));


    glGenBuffers(1, &_NBO);
    glBindBuffer(GL_ARRAY_BUFFER, _NBO);
    glBufferData(GL_ARRAY_BUFFER, 3 * _model->numIndices * sizeof(GLfloat), _model->normalArray, GL_STATIC_DRAW);
    glVertexAttribPointer(glGetAttribLocation(material._activeShader->_program, "in_Normal"), 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(glGetAttribLocation(material._activeShader->_program, "in_Normal"));


    glGenBuffers(1, &_TBO);
    glBindBuffer(GL_ARRAY_BUFFER, _TBO);
    glBufferData(GL_ARRAY_BUFFER, 2 * _model->numIndices * sizeof(GLfloat), _model->texCoordArray, GL_STATIC_DRAW);
    glVertexAttribPointer(glGetAttribLocation(material._activeShader->_program, "in_TexCoord"), 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(glGetAttribLocation(material._activeShader->_program, "in_TexCoord"));

    glGenBuffers(1, &_IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _model->numIndices * sizeof(GLuint), _model->indexArray, GL_STATIC_DRAW);
}

Renderable::~Renderable()
{
    
}