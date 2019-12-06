#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
    public:
        Camera();
        ~Camera();

        void setPosition(glm::vec3);
        void setLookPosition(glm::vec3);
        void setMatrix(glm::vec3, glm::vec3);
        void orbit(float, float);

        glm::vec3 _position;
        glm::vec3 _lookPosition;
        glm::mat4 _frustum;
        glm::mat4 _view;

    private:
        void updateViewMatrix();
};

#endif