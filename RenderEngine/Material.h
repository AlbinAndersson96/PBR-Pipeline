#ifndef MATERIAL_H
#define MATERIAL_H

#include "../Shaders/Shader.h"

#include "../Utilities/LoadTGA.h"

class Material
{
    public:
        Material(char*, char*, char*, char*, bool);
        ~Material();

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