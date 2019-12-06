#ifndef PBRMATERIAL_H
#define PBRMATERIAL_H

#include "Shaders/Shader.h"

#include "../Utilities/LoadTGA.h"

class PBRMaterial
{
    public:
        PBRMaterial(char*, char*, char*, char*);
        ~PBRMaterial();

        Shader *_pbrShader;

        unsigned int albedoMapID;
        unsigned int normalMapID;
        unsigned int metallicMapID;
        unsigned int roughnessMapID;
        //unsigned int ambientOcclusionMapID;

        void loadTextures();
};

#endif