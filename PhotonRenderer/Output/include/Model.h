#ifndef MODEL_H
#define MODEL_H
#include <string>
#include <assimp/Importer.hpp>
#include <vector>
#include "Mesh.h"

namespace Photon {
	class Model
	{
	public:
		Model(const std::string& path);
		void Draw();

	private:
		std::vector<Texture> m_texture_loaded;
		std::vector<Mesh> m_meshes;
	private:
		void loadModel(std::string path);

	};
}

#endif

