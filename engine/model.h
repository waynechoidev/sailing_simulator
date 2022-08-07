#pragma once

#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"
#include "texture.h"

class Model
{
public:
	Model();

	void loadModel(const std::string &fileName);
	void renderModel();
	void clearModel();

	~Model();

private:
	void loadNode(aiNode *node, const aiScene *scene);
	void loadMesh(aiMesh *mesh, const aiScene *scene);
	void loadMaterials(const aiScene *scene);

	std::vector<Mesh *> meshList;
	std::vector<Texture *> textureList;
	std::vector<unsigned int> meshToTex;
};
