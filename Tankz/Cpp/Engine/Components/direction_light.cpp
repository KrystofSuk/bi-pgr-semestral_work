#include "Engine/Components/direction_light.h"
#include "Engine/Core/game_object.h"


void DirectionLight::ProcessLight(Shader* shader, const std::string& index)
{
	glm::vec3 pos = transform->position;
	shader->SetFloat3f("dir.diffuse", diffuse * intensity);
	shader->SetFloat3f("dir.ambient", ambient * intensity);
	shader->SetFloat3f("dir.specular", specular * intensity);
	shader->SetFloat3f("dir.pos", glm::vec3(-pos[1], pos[2], -pos[0]));
	shader->SetFloat("dir.shininess", shininess);
}
