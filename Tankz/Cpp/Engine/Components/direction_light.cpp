#include "Engine/Components/direction_light.h"
#include "Engine/Core/game_object.h"


void DirectionLight::ProcessLight(Shader* shader, const std::string& index)
{
	glm::vec3 pos = transform->position;
	shader->SetFloat3f("dir.diffuse", diffuse * intensity);
	shader->SetFloat3f("dir.ambient", ambient * intensity);
	shader->SetFloat3f("dir.specular", specular * intensity);
	shader->SetFloat3f("dir.pos", pos);
	shader->SetFloat("dir.shininess", shininess);
}
