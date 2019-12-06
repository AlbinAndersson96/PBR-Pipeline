#ifndef PBRMATERIAL_H
#define PBRMATERIAL_H

#include "Shaders/Shader.h"

#include "../Utilities/LoadTGA.h"

class PBRMaterial
{
    public:
        PBRMaterial(char*, char*, char*, char*, bool);
        ~PBRMaterial();

        Shader *_pbrShader;
        Shader *_normalShader;

        Shader *_activeShader;

        unsigned int albedoMapID;
        unsigned int normalMapID;
        unsigned int metallicMapID;
        unsigned int roughnessMapID;
        //unsigned int ambientOcclusionMapID;

        void loadTextures();
        void SwapShader(bool);
};

#endif