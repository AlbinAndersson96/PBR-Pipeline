#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <glm/glm.hpp>

class PointLight
{
    public:
        PointLight(glm::vec3, glm::vec3);
        ~PointLight();

        glm::vec3 _position;
        glm::vec3 _color;
};

#endif