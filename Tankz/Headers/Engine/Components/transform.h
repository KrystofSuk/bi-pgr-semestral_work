#pragma once
#include <sstream>

#include "../component.h"
#include "pgr.h"


struct Transform : public Component {
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 size;

	Transform();
	Transform(const glm::vec3& p, const glm::vec3& r, const glm::vec3& s);

	void Scale(const glm::vec3& v);
	void Move(const glm::vec3& v);
	void Rotate(const glm::vec3& v);

	glm::vec3 Front() const;
	glm::vec3 Up() const;
	glm::vec3 Right() const;

	std::string Print() const;

	friend std::ostream& operator<<(std::ostream& out, const Transform& transform);

	~Transform();
};