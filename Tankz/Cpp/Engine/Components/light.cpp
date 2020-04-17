#include "Engine/Components/light.h"

Light::Light() :Component("Light")
{
	diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	specular = glm::vec3(1.0f, 1.0f, 1.0f);
	ambient = glm::vec3(0.1f, 0.1f, 0.1f);
	shininess = 10.0f;
	intensity = 1.0f;
}

std::string Light::Print() const
{
	return name;
}

Light::~Light()
{
}

std::ostream& operator<<(std::ostream& out, const Light& light)
{
	out << light.Print() << std::endl;
	return out;
}
