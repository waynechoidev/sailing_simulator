#include "camera.h"
#include <iostream>

Camera::Camera() {}

Camera::Camera(glm::vec3 startTarget)
{
	update(startTarget);
}

glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(position, target, up);
}

void Camera::update(glm::vec3 startTarget)
{
	position = {startTarget.x - 25.0f, startTarget.y - 25.0f, 50.0f};
	target = startTarget;
}

Camera::~Camera()
{
}
