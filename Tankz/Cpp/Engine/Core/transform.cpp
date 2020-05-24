#include "Engine/Core/transform.h"

sukkryst::Transform::Transform()
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	size = glm::vec3(1.0f, 1.0f, 1.0f);
}

sukkryst::Transform::Transform(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &size)
{
	this->position = position;
	this->rotation = rotation;
	this->size = size;
}

void sukkryst::Transform::Scale(const glm::vec3 &vector)
{
	size += vector;
}

void sukkryst::Transform::Move(const glm::vec3 &vector)
{
	position += vector;
}

void sukkryst::Transform::Rotate(const glm::vec3 &vector)
{
	rotation += vector;
}

void sukkryst::Transform::SetSize(const glm::vec3 &vector)
{
	size = vector;
}

void sukkryst::Transform::SetPos(const glm::vec3 &vector)
{
	position = vector;
}

void sukkryst::Transform::SetRot(const glm::vec3 &vector)
{
	rotation = vector;
}

glm::vec3 sukkryst::Transform::Front() const
{
	glm::vec3 front;
	front.x = cos(glm::radians(rotation[1])) * cos(glm::radians(rotation[0]));
	front.y = sin(glm::radians(rotation[0]));
	front.z = sin(glm::radians(rotation[1])) * cos(glm::radians(rotation[0]));
	return glm::normalize(front);
}

glm::vec3 sukkryst::Transform::Up() const
{
	return glm::cross(Front(), Right());
}

glm::vec3 sukkryst::Transform::Right() const
{
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	return glm::normalize(glm::cross(up, Front()));
}

sukkryst::Transform::~Transform()
{
}
