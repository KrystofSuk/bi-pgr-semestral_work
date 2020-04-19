#include "Engine/Components/point_light.h"
#include "Engine/Core/game_object.h"

PointLight::PointLight()
{
	type = 1;
}

void PointLight::ProcessLight(Shader* shader, const std::string& index)
{
	shader->SetFloat3f("poi[" + index + "].diffuse", diffuse * intensity);
	shader->SetFloat3f("poi[" + index + "].ambient", ambient * intensity);
	shader->SetFloat3f("poi[" + index + "].specular", specular * intensity);
	shader->SetFloat3f("poi[" + index + "].pos", transform->position);
	shader->SetFloat("poi[" + index + "].shininess", shininess);

	shader->SetFloat("poi[" + index + "].constant", 1.0f);
	shader->SetFloat("poi[" + index + "].linear", 0.35f);
	shader->SetFloat("poi[" + index + "].quadratic", 0.44f);
}