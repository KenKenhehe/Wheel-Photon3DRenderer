#ifndef PHOTON_ENTITY_H
#define PHOTON_ENTITY_H

#include <vector>
#include <glm\glm.hpp>
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Camera.h"
#include "Core.h"
#include "Texture.h"
#include "PhotonUtil.h"

namespace Photon
{
	class PHOTON_API Entity
	{
	public:
		Entity(glm::vec3 position) : m_position(position) {};

		void Translate(glm::vec3 translation)
		{
			m_model = glm::translate(m_model, translation);
			m_position += translation;
		}

		void Rotate(float angle, glm::vec3 axis)
		{
			m_model = glm::rotate(m_model, glm::radians(angle), axis);
		}

		void virtual Draw(Camera* camera = nullptr) {};
		void SetCamera(Camera* cam);
	protected:
		void virtual Dispose() {};
		bool virtual Init();
	protected:
		glm::vec3 m_position = glm::vec3(0, 0, 0);
		glm::mat4 m_model = glm::mat4(1.0f);

		VertexBuffer* m_vbo = nullptr;
		IndexBuffer* m_ibo = nullptr;
		VertexArray* m_vao = nullptr;

		std::vector<GLfloat> m_vertex_data_list;
		std::vector<GLuint> m_indices_list;

		GLfloat* m_vertices_ptr = nullptr;
		GLuint* m_indices_ptr = nullptr;

		Camera* m_target_camera;

		int m_screen_width;
		int m_screen_height;

		bool m_init_success;
	};
}
#endif // !PHOTON_ENTITY_H