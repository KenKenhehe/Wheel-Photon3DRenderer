#include "Plane.h"

namespace Photon
{
	Plane::Plane(float width, float height, glm::vec3 position) :
		Entity(position),
		m_width(width), m_height(height)
	{
		if (Init())
			LoadDefaultShader();
	}

	void Plane::Draw()
	{
		if (!m_init_success)
		{
			std::cout << "(Cube) ERROR: unable to draw due to unsuccessful initialization" << std::endl;
			return;
		}

		//glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
		////glm::mat4 model = glm::mat4(1.0);
		//glm::vec4 color = glm::vec4(1, 1, 1, 1);
		////model = glm::translate(model, pos);
		m_shader->Activate();

		if (m_texture != nullptr)
		{
			std::cout << "Binded texture on plane" << std::endl;
			m_texture->Bind();
		}

		if (m_target_camera != nullptr)
		{
			m_target_camera->SetUniform(*m_shader, "camMatrix");
		}
		m_shader->SetUniformMat4("model", m_model);

		m_vao->Bind();
		glDrawElements(GL_TRIANGLES, sizeof(GLuint) * m_indices_list.size() / sizeof(int), GL_UNSIGNED_INT, 0);
	}

	bool Plane::Init()
	{
		if (!Entity::Init())
			return false;

		// Vertices coordinates
		m_vertex_data_list =
		{ //     COORDINATES                     /   TexCoord    /       NORMALS     //
			-(m_width / 2), 0.0f,  (m_height / 2),	0.0f, 0.0f,	  0.0f, 1.0f, 0.0f,
			-(m_width / 2), 0.0f, -(m_height / 2),	0.0f, 1.0f,	  0.0f, 1.0f, 0.0f,
			 (m_width / 2), 0.0f, -(m_height / 2),	1.0f, 1.0f,	  0.0f, 1.0f, 0.0f,
			 (m_width / 2), 0.0f,  (m_height / 2),	1.0f, 0.0f,	  0.0f, 1.0f, 0.0f
		};

		// Indices for vertices order
		m_indices_list =
		{
			0, 1, 2,
			0, 2, 3
		};

		m_vertices_ptr = m_vertex_data_list.data();
		m_indices_ptr = m_indices_list.data();


		m_vao = new VertexArray();
		m_vao->Bind();
		int size = sizeof(GLfloat) * m_vertex_data_list.size();

		m_vbo = new VertexBuffer(m_vertices_ptr, sizeof(GLfloat) * m_vertex_data_list.size());
		m_ibo = new IndexBuffer(m_indices_ptr, sizeof(GLuint) * m_indices_list.size());

		m_vao->LinkAttrib(*m_vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
		m_vao->LinkAttrib(*m_vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(5 * sizeof(float)));
		m_vao->LinkAttrib(*m_vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(2 * sizeof(float)));

		m_vao->Unbind();
		m_vbo->Unbind();
		m_ibo->Unbind();

		m_model = glm::mat4(1.0);

		float position_final_x = map(m_position.x, 0, 800, -1, 1);
		float position_final_y = map(m_position.y, 0, 800, -1, 1);
		m_position.x = position_final_x;
		m_position.y = position_final_y;
		m_model = glm::translate(m_model, m_position);

		return true;
	}

	void Plane::LoadDefaultShader()
	{
		m_shader = new Shader("basic_model.vert", "basic_model.frag");
		m_shader->Activate();
		m_shader->SetUniformMat4("model", m_model);
		glm::vec4 objectColor = glm::vec4(1, 0, 0, 1);
		m_shader->SetUniformVec4("objectColor", objectColor);

	}
	void Plane::LoadShader(Shader& shader)
	{
		m_shader = &shader;
		m_shader->Activate();
	}
}
