#pragma once
#include <sstream>

#include "../component.h"
#include "pgr.h"


class Transform : public Component {
private:
	glm::vec3 _pos;
	glm::vec3 _rot;
	glm::vec3 _scale;
public:
	Transform();
	Transform(const glm::vec3& p, const glm::vec3& r, const glm::vec3& s);

	void Scale(const glm::vec3& v);
	void Move(const glm::vec3& v);
	void Rotate(const glm::vec3& v);

	const glm::vec3 GetPost() const;
	const glm::vec3 GetScale() const;
	const glm::vec3 GetRotation() const;

	std::string Print() const;

	friend std::ostream& operator<<(std::ostream& out, const Transform& transform);

	~Transform();
};