#pragma once
#include "vector"
#include "string"
#include "Shader.hpp"
#include "mesh.hpp"
#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"


class Model {

public:
	Model(char* path) {
		LoadModel(path);
	}
	void Draw(Shader& shader);
private:
	std::vector<Texture> texture_loaded;
	std::vector<Mesh> meshes;
	std::string directory;

	void LoadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};
