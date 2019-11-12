#include "Camera.h"

Camera::Camera()
:_position(glm::vec3(0, 0, -50))
,_lookPosition(glm::vec3(0, 0, 0))
,_frustum(glm::perspective(glm::radians(90.0f), 4.0f/3.0f, 0.1f, 100.0f))
,_view(glm::lookAt(_position, _lookPosition, glm::vec3(0, 1, 0)))
{}

Camera::~Camera()
{}

void Camera::setPosition(glm::vec3 position)
{
    _position = position;
    updateViewMatrix();
}

void Camera::setLookPosition(glm::vec3 position)
{
    _lookPosition = position;
    updateViewMatrix();
}

void Camera::orbit(float xAngle, float yAngle)
{
    glm::mat3 rotationAroundY = glm::mat3(
                                cos(xAngle), 0, sin(xAngle),
                                0, 1, 0,
                                -sin(xAngle), 0, cos(xAngle)
                                );
    glm::mat3 rotationAroundX = glm::mat3(
                                1, 0, 0,
                                0, cos(yAngle), -sin(yAngle),
                                0, sin(yAngle), cos(yAngle)
                                );
    glm::mat3 totalRotation = rotationAroundX * rotationAroundY;

    setPosition(_position * totalRotation);

}

void Camera::updateViewMatrix()
{
    _view = glm::lookAt(_position, _lookPosition, glm::vec3(0, 1, 0));
}