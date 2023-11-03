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
	class Light;
	//class InputManager;
	class PHOTON_API Entity
	{
	public:
		Entity(glm::vec3 position) : m_position(position) {};

		void Translate(glm::vec3 translation)
		{
			m_model = glm::translate(m_model, translation);
			m_position = glm::vec3(m_model[3]);
		}

		void SetPosition(glm::vec3 pos) {
			m_position = pos;
			glm::mat4 identity = glm::mat4(1.0);
			m_model = glm::translate(identity, pos);
		}

		glm::vec3 GetPosition() { 
			m_position = glm::vec3(m_model[3]);
			return m_position; 
		}

		void Rotate(float angle, glm::vec3 axis)
		{
			m_model = glm::rotate(m_model, glm::radians(angle), axis);
			m_position = glm::vec3(m_model[3]);
		}

		void Rotate(glm::vec3 rotation_to_add)
		{
			glm::vec3 new_rotation =  m_rotation + rotation_to_add;
			SetRotation(rotation_to_add);
		}

		void SetRotation(glm::vec3 rotation) 
		{
			m_rotation = rotation;

			m_model = glm::rotate(m_model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
			m_model = glm::rotate(m_model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
			m_model = glm::rotate(m_model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
			m_position = glm::vec3(m_model[3]);
		}

		glm::vec3 GetRotation() {
			return m_rotation;
		}

		glm::mat4 GetModelMatrix() {
			return m_model;
		}

		/*void SetModelMatrix(glm::mat4 model_matrix) 
		{
			m_model = model_matrix;
		}*/

		void virtual Draw(Camera* camera = nullptr) {};

		void SetCamera(Camera* cam);
		Camera* GetCamera() { return m_target_camera; }

		void AddLightSource(Light* light_source);
		Shader* GetShader() { return m_shader; };

		void SetCurrentAppPath(std::string path) { m_current_app_path = path; }
		std::string GetCurrentPath() { return m_current_app_path; }

	protected:
		void virtual Dispose() {};
		bool virtual Init();
		
	protected:
		glm::mat4 m_model = glm::mat4(1.0f);
		glm::vec3 m_position = glm::vec3(m_model[3]);
		glm::vec3 m_rotation = glm::vec3(0);

		VertexBuffer* m_vbo = nullptr;
		IndexBuffer* m_ibo = nullptr;
		VertexArray* m_vao = nullptr;

		std::vector<GLfloat> m_vertex_data_list;
		std::vector<GLuint> m_indices_list;

		GLfloat* m_vertices_ptr = nullptr;
		GLuint* m_indices_ptr = nullptr;

		Camera* m_target_camera = nullptr;

		Shader* m_shader = nullptr;

		int m_screen_width = 0;
		int m_screen_height = 0;

		bool m_init_success = false;
		bool m_has_texture = false;

		std::string m_current_app_path;
		//InputManager m_input_manager;
	};
}
#endif // !PHOTON_ENTITY_H