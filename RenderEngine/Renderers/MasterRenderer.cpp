#include "MasterRenderer.h"

MasterRenderer::MasterRenderer(Camera *camera, PointLight *pointLights, int nrOfLights)
:_camera(camera)
,_pointLights(pointLights)
,_nrOfLights(nrOfLights)
{
    _modelRenderer = new ModelRenderer();
    _skyboxShader = new Shader("RenderEngine/Shaders/SkyboxShader.vert", "RenderEngine/Shaders/SkyboxShader.frag");
}

MasterRenderer::~MasterRenderer()
{
    delete _modelRenderer;
    delete _skyboxShader;
}

GLfloat animation = 0.0f;

void MasterRenderer::render(Renderable object, Cubemap cubemap)
{
    switch (object._tag)
    {
    case Mesh:
        _modelRenderer->render(_camera, object, _pointLights, _nrOfLights, cubemap);
        break;
    default:
        break;
    }
}

void MasterRenderer::renderCubemap(Cubemap cubeMap)
{
    GLfloat cubeVerts[] = {
        // front
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    };

    glUseProgram(_skyboxShader->_program);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 3 * 36 * sizeof(GLfloat), cubeVerts, GL_STATIC_DRAW);
    glVertexAttribPointer(glGetAttribLocation(_skyboxShader->_program, "aPos"), 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(glGetAttribLocation(_skyboxShader->_program, "aPos"));

    _skyboxShader->setMat4Uniform("projection", _camera->_frustum);
    _skyboxShader->setMat4Uniform("view", _camera->_view);

    _skyboxShader->setIntUniform("equirectangularMap", 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap._texture);

    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}