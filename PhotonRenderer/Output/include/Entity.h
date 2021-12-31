#include <vector>
#include <glm\glm.hpp>
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Camera.h"
#include "Core.h"

class PHOTON_API Entity
{
public:
	Entity(glm::vec3 position): m_position(position) {};

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
protected:
	
	void virtual Dispose() {};
	void virtual Init() {};

	

protected:
	glm::vec3 m_position = glm::vec3(0, 0, 0);
	glm::mat4 m_model = glm::mat4(1.0f);

	VertexBuffer* m_vbo = nullptr;
	IndexBuffer* m_ibo = nullptr;
	VertexArray m_vao;

	std::vector<GLfloat> m_vertex_data_list;
	std::vector<GLuint> m_indices_list;

	GLfloat* m_vertices_ptr = nullptr;
	GLuint* m_indices_ptr = nullptr;
};