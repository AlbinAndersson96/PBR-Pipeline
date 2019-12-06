#ifndef MASTERRENDERER_H
#define MASTERRENDERER_H

#include <iostream>

#include "ModelRenderer.h"
#include "../Renderable.h"
#include "../Camera.h"
#include "../PointLight.h"
#include "../Cubemap.h"
#include "../Shaders/Shader.h"

class MasterRenderer
{
    public:
        MasterRenderer(Camera*, PointLight*, int);
        ~MasterRenderer();
        void render(Renderable, Cubemap);
        void renderCubemap(Cubemap);

    private:
        ModelRenderer *_modelRenderer;
        Camera *_camera;
        PointLight *_pointLights;
        int _nrOfLights;
        Shader *_skyboxShader;
};

#endif