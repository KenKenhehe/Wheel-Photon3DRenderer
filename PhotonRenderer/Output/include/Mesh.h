#ifndef MESH_H
#define MESH_H
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#define MAX_BONE_INFLUENCE 4

namespace Photon {
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 tex_coord;
		glm::vec3 tangent;
		glm::vec3 bitangent;

		int bone_ids[MAX_BONE_INFLUENCE];
		float weights[MAX_BONE_INFLUENCE];
	};

	struct Texture
	{
		unsigned int id;
		std::string type;
	};

	class Mesh
	{
	public:
		Mesh(std::vector<Vertex> vertices,
			std::vector<unsigned int> indices,
			std::vector<Texture> textures);

		void Draw(Shader& shader);

	private:
		std::vector<Vertex> m_vertices;
		std::vector<GLuint> m_indices;
		std::vector<Texture> m_textures;

		VertexBuffer* m_vbo = nullptr;
		IndexBuffer* m_ibo = nullptr;
		VertexArray* m_vao = nullptr;


	private:
		void SetupMesh();
	};
}
#endif

