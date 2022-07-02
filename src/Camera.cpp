#include "pch.h"
#include "Camera.h"

Camera::Camera(vec3 pos, vec3 lookAt) :
	position(pos),
	lookAt(lookAt),
	fov(90),
	forward(glm::normalize(lookAt - pos)),
	up(vec3(0, 1, 0)),
	transformation(1)
{
	transformation = glm::lookAt(position, lookAt, up);
}

Camera::~Camera()
{

}

void Camera::moveForward(f32 value)
{
	position += forward * value;
}

void Camera::moveRight(f32 value)
{
	vec3 v = glm::normalize(
		glm::cross(
			glm::normalize(forward),
			glm::normalize(up)
		)
	) * value;

	position += v;
}

void Camera::moveUp(f32 value)
{
	position += up * value;
}

void Camera::updateTransformation()
{
	transformation = glm::lookAt(position, position + forward, up);
}

mat4 Camera::getTransformation() const
{
	return transformation;
}