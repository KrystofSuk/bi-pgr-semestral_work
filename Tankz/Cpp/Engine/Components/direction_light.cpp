#include "..\..\..\Headers\Engine\Components\direction_light.h"
#include "../../../Headers/Engine/game_object.h"

void DirectionLight::ProcessLight(Shader* shader)
{
	glm::vec3 pos = static_cast<GameObject*>(gameObject)->transform->position;
	intensity = 0.2f;
	shader->SetFloat3f("dir.diffuse", diffuse * intensity);
	shader->SetFloat3f("dir.ambient", ambient * intensity);
	shader->SetFloat3f("dir.specular", specular * intensity);
	shader->SetFloat3f("dir.pos", glm::vec3(-pos[1], pos[2], -pos[0]));
	shader->SetFloat("dir.shininess", shininess);
}
