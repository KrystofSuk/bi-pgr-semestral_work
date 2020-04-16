#include "..\..\..\Headers\Engine\Components\transform.h"

Transform::Transform() : Component("Transform")
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	size = glm::vec3(1.0f, 1.0f, 1.0f);
}

Transform::Transform(const glm::vec3& p, const glm::vec3& r, const glm::vec3& s) : Component("Transform")
{
	position = p;
	rotation = r;
	size = s;
}

void Transform::Scale(const glm::vec3& v)
{
	size += v;
}

void Transform::Move(const glm::vec3& v)
{
	position += v;
}

void Transform::Rotate(const glm::vec3& v)
{
	rotation += v;
	std::cout << Print() << std::endl;
}


glm::vec3 Transform::Front() const
{
	glm::vec3 front;
	front.x = cos(glm::radians(rotation[1])) * cos(glm::radians(rotation[0]));
	front.y = sin(glm::radians(rotation[0]));
	front.z = sin(glm::radians(rotation[1])) * cos(glm::radians(rotation[0]));
	return glm::normalize(front);
}


glm::vec3 Transform::Up() const
{
	return glm::cross(Front(), Right());
}


glm::vec3 Transform::Right() const
{
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	return glm::normalize(glm::cross(up, Front()));
}

std::string Transform::Print() const
{
	std::stringstream s;
	s << name << std::endl << "P:  " << position.x << "," << position.y << "," << position.z << std::endl << "S:  " << size.x << "," << size.y << "," << size.z << std::endl << "R:  " << rotation.x << "," << rotation.y << "," << rotation.z;
	return s.str();
}

Transform::~Transform()
{
}

std::ostream& operator<<(std::ostream& out, const Transform& transform)
{
	out << transform.Print() << std::endl;
	return out;
}
