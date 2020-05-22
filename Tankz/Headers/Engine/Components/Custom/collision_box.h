#pragma once

#include "Engine/Core/component.h"
#include "Engine/Core/spline.h"

struct CollisionBox : public Component {

	glm::vec3 size;
	float yMin;

	CollisionBox(const glm::vec3& box);

	void Update();


	std::string Print() const;

	friend std::ostream& operator<<(std::ostream& out, const CollisionBox& component);

	~CollisionBox();
};