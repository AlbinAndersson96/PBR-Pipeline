#include "MasterRenderer.h"

MasterRenderer::MasterRenderer(Camera *camera)
:_camera(camera)
{
    _modelRenderer = new ModelRenderer();
}

MasterRenderer::~MasterRenderer()
{
    delete _modelRenderer;
}

GLfloat animation = 0.0f;

void MasterRenderer::render(Renderable object)
{


    switch (object._tag)
    {
    case Mesh:
        _modelRenderer->render(_camera, object);
        break;
    default:
        break;
    }
}