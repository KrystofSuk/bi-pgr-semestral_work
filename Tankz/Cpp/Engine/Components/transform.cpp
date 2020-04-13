﻿#include "..\..\..\Headers\Engine\Components\transform.h"

Transform::Transform() : Component("Transform")
{
}

Transform::Transform(const glm::vec3& p, const glm::vec3& r, const glm::vec3& s) : Component("Transform")
{
	_pos = p;
	_rot = r;
	_scale = s;
}

void Transform::Scale(const glm::vec3& v)
{
	_scale += v;
}

void Transform::Move(const glm::vec3& v)
{
	_pos += v;
}

void Transform::Rotate(const glm::vec3& v)
{
	_rot += v;
}

const glm::vec3 Transform::GetPost() const
{
	return _pos;
}

const glm::vec3 Transform::GetScale() const
{
	return _scale;
}

const glm::vec3 Transform::GetRotation() const
{
	return _rot;
}

std::string Transform::Print() const
{
	std::stringstream s;
	s << _name << std::endl << "P:  " << _pos.x << "," << _pos.y << "," << _pos.z << std::endl << "S:  " << _scale.x << "," << _scale.y << "," << _scale.z << std::endl << "R:  " << _rot.x << "," << _rot.y << "," << _rot.z;
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
