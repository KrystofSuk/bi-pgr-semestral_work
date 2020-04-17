#include "..\..\..\Headers\Engine\Components\mesh_renderer.h"

//**************************************************************************************************
/// Checks whether vector is zero-length or not.
bool isVectorNull(const glm::vec3& vect) {

	return !vect.x && !vect.y && !vect.z;
}

//**************************************************************************************************
/// Align (rotate and move) current coordinate system to given parameters.
/**
 This function works similarly to \ref gluLookAt, however it is used for object transform
 rather than view transform. The current coordinate system is moved so that origin is moved
 to the \a position. Object's local front (-Z) direction is rotated to the \a front and
 object's local up (+Y) direction is rotated so that angle between its local up direction and
 \a up vector is minimum.

 \param[in]  position           Position of the origin.
 \param[in]  front              Front direction.
 \param[in]  up                 Up vector.
 */
glm::mat4 alignObject(const glm::vec3& position, const glm::vec3& front, const glm::vec3& up) {

	glm::vec3 z = -glm::normalize(front);

	if (isVectorNull(z))
		z = glm::vec3(0.0, 0.0, 1.0);

	glm::vec3 x = glm::normalize(glm::cross(up, z));

	if (isVectorNull(x))
		x = glm::vec3(1.0, 0.0, 0.0);

	glm::vec3 y = glm::cross(z, x);
	//mat4 matrix = mat4(1.0f);
	glm::mat4 matrix = glm::mat4(
		x.x, x.y, x.z, 0.0,
		y.x, y.y, y.z, 0.0,
		z.x, z.y, z.z, 0.0,
		position.x, position.y, position.z, 1.0
	);

	return matrix;
}


MeshRenderer::MeshRenderer(Mesh* mesh, Material* material) : Component("MeshRenderer")
{
	_mesh = mesh;
	_material = material;
}

void MeshRenderer::Draw(const glm::mat4& p, const glm::mat4& v, Transform* t, std::vector<Light*> lights, Transform* c)
{
	glm::mat4 m = glm::translate(glm::mat4(1.0f), t->position);
	m = glm::rotate(m, glm::radians(t->rotation[0]), glm::vec3(1, 0, 0));
	m = glm::rotate(m, glm::radians(t->rotation[1]), glm::vec3(0, 1, 0));
	m = glm::rotate(m, glm::radians(t->rotation[2]), glm::vec3(0, 0, 1));
	m = glm::scale(m, t->size);

	glm::mat4 PVM = p * v * m;

	glm::mat4 normalMatrix = glm::transpose(glm::inverse(glm::mat4(glm::mat3(m))));


	Shader* shader = _material->shader;

	shader->Use();
	//shader->SetFloat4f("input_color", glm::vec4(_material->diffuse, 1.0));
	shader->SetFloatMatrix4f("PVM", PVM);
	shader->SetFloatMatrix4f("V", v);
	shader->SetFloatMatrix4f("M", m);
	shader->SetFloatMatrix4f("NM", normalMatrix);


	shader->SetInt("point", 2);
	shader->SetInt("spot", 1);

	lights[0]->ProcessLight(shader);
	for (int i = 0; i < 2; i++) {
		lights[i + 1]->ProcessLight(shader, std::to_string(i));
	}
	for (int i = 0; i < 1; i++) {
		lights[i + 3]->ProcessLight(shader, std::to_string(i));
	}

	if (_mesh->texture != 0) {
		shader->SetInt("texSampler", 0);
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(GL_TEXTURE_2D, _mesh->texture);
	}

	glBindVertexArray(_mesh->vao);
	glDrawElements(GL_TRIANGLES, _mesh->faces * 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


std::string MeshRenderer::Print() const
{
	return name;
}

MeshRenderer::~MeshRenderer()
{
}

std::ostream& operator<<(std::ostream& out, const MeshRenderer& renderer)
{
	out << renderer.Print() << std::endl;
	return out;
}




