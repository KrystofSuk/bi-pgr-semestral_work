#include "Engine/Components/light.h"

sukkryst::Light::Light() : Component("Light")
{
	diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	specular = glm::vec3(1.0f, 1.0f, 1.0f);
	ambient = glm::vec3(0.1f, 0.1f, 0.1f);
	shininess = 10.0f;
	intensity = 1.0f;
}

sukkryst::Light::~Light()
{
}

void sukkryst::Light::OnClick()
{
	on = !on;
}
