#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
    public:
        Shader(char*, char*);
        ~Shader();

        unsigned int _program;
        
        void use();

        void setIntUniform(char*, int);
        void setFloatUniform(char*, float);
        void setMat4Uniform(char*, glm::mat4);
        void setVec3Uniform(char*, glm::vec3, int);
};

#endif