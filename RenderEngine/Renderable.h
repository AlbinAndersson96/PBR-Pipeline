#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "Material.h"

extern "C"
{
    #include "../Utilities/loadobj.h"
}

enum Tag
{
    Mesh
    ,Cube
    ,Skybox
};

class Renderable
{
    public:
        Renderable(char*, Material, Tag);
        ~Renderable();


        Model *_model;
        Material _material;
        Tag _tag;

        unsigned int _VAO;

        unsigned int _VBO;
        unsigned int _IBO;
        unsigned int _NBO;
        unsigned int _TBO;
};

#endif