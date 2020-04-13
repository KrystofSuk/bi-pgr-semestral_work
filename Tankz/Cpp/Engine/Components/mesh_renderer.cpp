﻿#include "..\..\..\Headers\Engine\Components\mesh_renderer.h"

Mesh::Mesh(float* verts, float size, Shader* shader)
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, verts, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(shader->GetLocation("position"));
	glVertexAttribPointer(shader->GetLocation("position"), 3, GL_FLOAT, GL_FALSE, 0, 0);

	vert = size;
}

Mesh::Mesh(const aiScene* scene, Shader* shader)
{

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
}


MeshRenderer::MeshRenderer(float* verts, float size, Shader* shader)
{
	_mesh = new Mesh(verts, size, shader);
	CHECK_GL_ERROR();
	_shader = shader;
}

MeshRenderer::MeshRenderer(const std::string& filename, Shader* shader)
{
	Assimp::Importer imp;
	imp.SetPropertyInteger(AI_CONFIG_PP_PTV_NORMALIZE, 1);
	const aiScene* scene = imp.ReadFile(filename.c_str(), 0 | aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_PreTransformVertices | aiProcess_JoinIdenticalVertices);
	if (!scene)
	{
		std::cout << "Error loading mesh: " << filename << std::endl << "Error: " << imp.GetErrorString() << std::endl;
		return;
	}

	_mesh = new Mesh(scene, shader);
	_shader = shader;

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

	CHECK_GL_ERROR();
	std::cout << "Loaded mesh: " << filename << std::endl;
}

void MeshRenderer::Draw()
{
	_shader->Use();
	_shader->SetFloat4f("input_color", glm::vec4(1.0, 1.0, 0.0, 1.0));
	glBindVertexArray(_mesh -> vao);
	glDrawElements(GL_TRIANGLES, _mesh -> faces * 3, GL_UNSIGNED_INT, 0);
}


std::string MeshRenderer::Print() const
{
	return std::string();
}

MeshRenderer::~MeshRenderer()
{
	delete _mesh;
}

std::ostream& operator<<(std::ostream& out, const MeshRenderer& renderer)
{
	out << renderer.Print() << std::endl;
	return out;
}

