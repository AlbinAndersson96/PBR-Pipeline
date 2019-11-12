#ifndef MODELRENDERER_H
#define MODELRENDERER_H

#include "../Shaders/PBRShader.h"
#include "../Camera.h"
#include "../Renderable.h"

#include <iostream>

class ModelRenderer
{
    public:
        ModelRenderer();
        ~ModelRenderer();

        void render(Camera *, Renderable);

    private:
        PBRShader *_pbrShader;
};

#endif