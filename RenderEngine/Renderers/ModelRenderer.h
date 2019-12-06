#ifndef MODELRENDERER_H
#define MODELRENDERER_H

#include "../Camera.h"
#include "../Renderable.h"
#include "../PointLight.h"
#include "../Cubemap.h"

#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

class ModelRenderer
{
    public:
        ModelRenderer();
        ~ModelRenderer();

        void render(Camera*, Renderable, PointLight*, int, Cubemap);
};

#endif