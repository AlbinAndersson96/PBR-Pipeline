#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "PBRMaterial.h"

extern "C"
{
    #include "../Utilities/loadobj.h"
}

enum Tag
{
    Mesh
    ,Cube
};

class Renderable
{
    public:
        Renderable(char*, PBRMaterial, Tag);
        ~Renderable();


        Model *_model;
        PBRMaterial _material;
        Tag _tag;

        unsigned int _VAO;

        unsigned int _VBO;
        unsigned int _IBO;
        unsigned int _NBO;
        unsigned int _TBO;
};

#endif