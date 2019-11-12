#ifndef PBRSHADER_H
#define PBRSHADER_H

#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class PBRShader
{
    public:
        PBRShader();
        ~PBRShader();

        GLuint _program;

        void use(glm::mat4, glm::mat4, glm::vec3);

    private:
};

#endif