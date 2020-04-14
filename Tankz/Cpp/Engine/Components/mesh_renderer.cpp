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


Mesh::Mesh(const std::string& filename, Shader* shader)
{
	Assimp::Importer imp;
	imp.SetPropertyInteger(AI_CONFIG_PP_PTV_NORMALIZE, 1);
	const aiScene* scene = imp.ReadFile(filename.c_str(), 0 | aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_PreTransformVertices | aiProcess_JoinIdenticalVertices);
	if (!scene)
	{
		std::cout << "Error loading mesh: " << filename << std::endl << "Error: " << imp.GetErrorString() << std::endl;
		return;
	}

	const aiMesh* loadedMesh = scene->mMeshes[0];

	faces = loadedMesh->mNumFaces;
	vert = loadedMesh->mNumVertices;

	unsigned int offset = 0;
	int sVBO = 6;
	//If we expect texture coords
	if (loadedMesh->HasTextureCoords(0))
		sVBO += 2;

#pragma region VBO

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sVBO * sizeof(float) * loadedMesh->mNumVertices, 0, GL_STATIC_DRAW);
	//Verts
	glBufferSubData(GL_ARRAY_BUFFER, offset, 3 * sizeof(float) * loadedMesh->mNumVertices, loadedMesh->mVertices);
	offset = 3 * sizeof(float) * loadedMesh->mNumVertices;

	//Normals
	glBufferSubData(GL_ARRAY_BUFFER, offset, 3 * sizeof(float) * loadedMesh->mNumVertices, loadedMesh->mVertices);
	offset *= 2;

	//Texture
	if (loadedMesh->HasTextureCoords(0)) {
		float* textureCoords = new float[2 * loadedMesh->mNumVertices];
		float* currentCoord = textureCoords;

		aiVector3D coord;
		for (unsigned int i = 0; i < loadedMesh->mNumVertices; i++) {
			coord = (loadedMesh->mTextureCoords[0])[i];
			*currentCoord++ = coord.x;
			*currentCoord++ = coord.y;
		}

		glBufferSubData(GL_ARRAY_BUFFER, offset, 2 * sizeof(float) * loadedMesh->mNumVertices, textureCoords);
	}
	CHECK_GL_ERROR();

#pragma endregion 

#pragma region EBO

	GLuint* faces = new GLuint[loadedMesh->mNumFaces * 3];
	for (unsigned int i = 0; i < loadedMesh->mNumFaces; i++) {
		faces[i * 3 + 0] = loadedMesh->mFaces[i].mIndices[0];
		faces[i * 3 + 1] = loadedMesh->mFaces[i].mIndices[1];
		faces[i * 3 + 2] = loadedMesh->mFaces[i].mIndices[2];
	}

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(unsigned) * loadedMesh->mNumFaces, faces, GL_STATIC_DRAW);

	delete[] faces;
	CHECK_GL_ERROR();

#pragma endregion 

#pragma region VAO

	offset = 3 * sizeof(float) * loadedMesh->mNumVertices;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glEnableVertexAttribArray(shader->GetLocation("position"));
	glVertexAttribPointer(shader->GetLocation("position"), 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(shader->GetLocation("normal"));
	glVertexAttribPointer(shader->GetLocation("normal"), 3, GL_FLOAT, GL_FALSE, 0, (void*)offset);

	if (loadedMesh->HasTextureCoords(0)) {
		offset *= 2;
		glEnableVertexAttribArray(shader->GetLocation("texCoord"));
		glVertexAttribPointer(shader->GetLocation("texCoord"), 2, GL_FLOAT, GL_FALSE, 0, (void*)offset);
	}

	CHECK_GL_ERROR();

	glBindVertexArray(0);

#pragma endregion

#pragma region Tex

	const aiMaterial* materal = scene->mMaterials[scene->mMeshes[0]->mMaterialIndex];

	if (materal->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
		aiString path;

		materal->GetTexture(aiTextureType_DIFFUSE, 0, &path);

		std::string name = path.data;

		size_t found = filename.find_last_of("/\\");

		if (found != std::string::npos) {
			name.insert(0, filename.substr(0, found + 1));
		}

		_texture = pgr::createTexture(name);
	}

#pragma endregion
}


MeshRenderer::MeshRenderer(Mesh* mesh, Material* material) : Component("MeshRenderer")
{
	_mesh = mesh;
	_material = material;
}

void MeshRenderer::Draw(const glm::mat4& p, const glm::mat4& v, Transform* t)
{
	glm::mat4 m = glm::translate(glm::mat4(1.0f), t->GetPos());
	m = glm::rotate(m, glm::radians(t->GetRotation()[0]), glm::vec3(1, 0, 0));
	m = glm::rotate(m, glm::radians(t->GetRotation()[1]), glm::vec3(0, 1, 0));
	m = glm::rotate(m, glm::radians(t->GetRotation()[2]), glm::vec3(0, 0, 1));
	m = glm::scale(m, t->GetScale());

	glm::mat4 PVM = p * v * m;

	Shader* shader = _material->shader;

	shader->Use();
	shader->SetFloat4f("input_color", glm::vec4(_material->diffuse, 1.0));
	shader->SetFloatMatrix4f("PVMmatrix", PVM);

	glBindVertexArray(_mesh->vao);
	glDrawElements(GL_TRIANGLES, _mesh->faces * 3, GL_UNSIGNED_INT, 0);
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




