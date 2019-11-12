#ifndef MASTERRENDERER_H
#define MASTERRENDERER_H

#include <iostream>

#include "ModelRenderer.h"
#include "../Renderable.h"
#include "../Camera.h"

class MasterRenderer
{
    public:
        MasterRenderer(Camera *camera);
        ~MasterRenderer();
        void render(Renderable);

    private:
        ModelRenderer *_modelRenderer;
        Camera *_camera;
};

#endif