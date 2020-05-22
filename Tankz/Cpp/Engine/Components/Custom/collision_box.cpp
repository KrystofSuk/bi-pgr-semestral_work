#include "..\..\..\..\Headers\Engine\Components\Custom\collision_box.h"

CollisionBox::CollisionBox(const glm::vec3& box) : Component("CollisionBox")
{
	size = box;
}

void CollisionBox::Update()
{
	if (transform->position.x > size.x) {
		transform->position.x = size.x;
	}
	if (transform->position.x < -size.x) {
		transform->position.x = -size.x;
	}
	if (transform->position.y > size.y) {
		transform->position.y = size.y;
	}
	if (transform->position.y < yMin) {
		transform->position.y = yMin;
	}
	if (transform->position.z > size.z) {
		transform->position.z = size.z;
	}
	if (transform->position.z < -size.z) {
		transform->position.z = -size.z;
	}
}


std::string CollisionBox::Print() const
{
	return std::string();
}

CollisionBox::~CollisionBox()
{
}

std::ostream& operator<<(std::ostream& out, const CollisionBox& component)
{
	return out << component.Print();
}
