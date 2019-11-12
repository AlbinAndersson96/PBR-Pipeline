#ifndef MATERIAL_H
#define MATERIAL_H

#include "../Utilities/LoadTGA.h"

class Material
{
    public:
        Material(char*);
        ~Material();

        unsigned int textureID;
};

#endif