#include "Renderable.h"

Renderable::Renderable(char *modelPath, Material material, Tag tag)
:_material(material)
,_tag(tag)
{
    _model = LoadModelPlus(modelPath);

    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);

    glGenBuffers(1, &_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, 3 * _model->numVertices * sizeof(GLfloat), _model->vertexArray, GL_STATIC_DRAW);

    glGenBuffers(1, &_NBO);
    glBindBuffer(GL_ARRAY_BUFFER, _NBO);
    glBufferData(GL_ARRAY_BUFFER, 3 * _model->numIndices * sizeof(GLfloat), _model->normalArray, GL_STATIC_DRAW);

    glGenBuffers(1, &_TBO);
    glBindBuffer(GL_ARRAY_BUFFER, _TBO);
    glBufferData(GL_ARRAY_BUFFER, 2 * _model->numIndices * sizeof(GLfloat), _model->texCoordArray, GL_STATIC_DRAW);

    glGenBuffers(1, &_IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _model->numIndices * sizeof(GLuint), _model->indexArray, GL_STATIC_DRAW);
}

Renderable::~Renderable()
{
    
}