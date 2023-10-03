#ifndef MODEL_H
#define MODEL_H
#include <string>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <vector>
#include "Mesh.h"

namespace Photon {
	class PHOTON_API Model
	{
	public:
		Model(const std::string& path);
		void Draw(Shader& shader);

	private:
		std::vector<Texture> m_texture_loaded;
		std::vector<Mesh> m_meshes;
		std::string directory;
	private:
		void loadModel(const std::string& path);
		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);

		unsigned int LoadTextureFromFile(const char* path, const std::string& directory, bool gamma);
	};
}

#endif

