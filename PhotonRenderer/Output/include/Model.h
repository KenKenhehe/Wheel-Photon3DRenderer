#ifndef MODEL_H
#define MODEL_H
#include <string>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <vector>
#include <stb\stb_image.h>
#include "Mesh.h"
#include "Entity.h"

namespace Photon {
	class PHOTON_API Model: public Entity
	{
	public:
		Model(const std::string& path, glm::vec3 pos);
		void Draw();
		 
	private:
		std::vector<TextureData> m_texture_loaded;
		std::vector<Mesh> m_meshes;
		std::string m_directory;
	private:
		void loadModel(const std::string& path);
		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);

		unsigned int LoadTextureFromFile(const char* path, const std::string& m_directory);
		std::vector<TextureData> LoadMaterialTextures(aiMaterial* material, aiTextureType type, std::string type_name);
	};
}

#endif

