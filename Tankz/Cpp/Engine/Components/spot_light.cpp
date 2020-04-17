#include "..\..\..\Headers\Engine\Components\spot_light.h"
#include "../../../Headers/Engine/game_object.h"

void SpotLight::ProcessLight(Shader* shader, const std::string& index)
{
	glm::vec3 pos = static_cast<GameObject*>(gameObject)->transform->position;
	glm::vec3 dir = static_cast<GameObject*>(gameObject)->transform->Front();

	shader->SetFloat3f("spo[" + index + "].diffuse", diffuse * intensity);
	shader->SetFloat3f("spo[" + index + "].ambient", ambient * intensity);
	shader->SetFloat3f("spo[" + index + "].specular", specular * intensity);
	shader->SetFloat3f("spo[" + index + "].pos", pos);
	shader->SetFloat3f("spo[" + index + "].dir", dir);
	shader->SetFloat("spo[" + index + "].shininess", shininess);

	shader->SetFloat("spo[" + index + "].cutOff", 0.91f);
	shader->SetFloat("spo[" + index + "].outerCutOff", 0.82f);

	shader->SetFloat("spo[" + index + "].constant", 1.0f);
	shader->SetFloat("spo[" + index + "].linear", 0.35f);
	shader->SetFloat("spo[" + index + "].quadratic", 0.44f);
}