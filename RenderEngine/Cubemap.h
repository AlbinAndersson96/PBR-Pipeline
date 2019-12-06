#ifndef CUBEMAP_H
#define CUBEMAP_H

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Shaders/Shader.h"

#include "../Utilities/LoadTGA.h"

class Cubemap
{
    public:
        Cubemap(char*);
        ~Cubemap();

        unsigned int _texture;
        unsigned int _convolutedTexture;
        unsigned int _mipmapTexture;
        unsigned int _brdfConvolutedTexture;

        Shader *_cubemapProgram;
        Shader *_convolutionProgram;
        Shader *_hammerslyProgram;
        Shader *_BRDFConvolutionProgram;

    private:
        void renderCube(Shader*);
        void renderQuad(Shader*);
};

#endif