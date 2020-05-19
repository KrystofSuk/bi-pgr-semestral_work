#include "Engine/Components/spot_light.h"
#include "Engine/Core/game_object.h"

SpotLight::SpotLight()
{
	type = 2;
}

void SpotLight::ProcessLight(Shader* shader, const std::string& index)
{
	glm::vec3 pos = transform->position;//static_cast<GameObject*>(gameObject)->transform->position;
	glm::vec3 dir = transform->Front();

	if (on) {
		shader->SetFloat3f("spo[" + index + "].diffuse", diffuse * intensity);
		shader->SetFloat3f("spo[" + index + "].ambient", ambient * intensity);
		shader->SetFloat3f("spo[" + index + "].specular", specular * intensity);
	}
	if (!on) {
		shader->SetFloat3f("spo[" + index + "].diffuse", diffuse * 0.0f);
		shader->SetFloat3f("spo[" + index + "].ambient", ambient * 0.0f);
		shader->SetFloat3f("spo[" + index + "].specular", specular * 0.0f);
	}

	shader->SetFloat3f("spo[" + index + "].pos", pos);
	shader->SetFloat3f("spo[" + index + "].dir", dir);
	shader->SetFloat("spo[" + index + "].shininess", shininess);

	shader->SetFloat("spo[" + index + "].cutOff", 0.5f);
	shader->SetFloat("spo[" + index + "].outerCutOff", 0.4f);

	shader->SetFloat("spo[" + index + "].constant", 1.0f);
	shader->SetFloat("spo[" + index + "].linear", 0.3f);
	shader->SetFloat("spo[" + index + "].quadratic", 0.1f);
}