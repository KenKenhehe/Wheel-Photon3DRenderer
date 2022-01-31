#include "Line.h"

namespace Photon
{
	Line::Line(glm::vec3 start, glm::vec3 end) :
		Entity(glm::vec3(0)), m_start(start), m_end(end)
	{
		if (Init() == true)
			LoadDefaultShader();
	}

	Line::Line(glm::vec2 start, glm::vec2 end) :
		Entity(glm::vec3(0)),
		m_start(glm::vec3(start.x, start.y, 0)),
		m_end(glm::vec3(end.x, end.y, 0))
	{
		if (Init() == true)
			LoadDefaultShader();
	}


	void Line::Draw(Camera* cam)
	{
		if (!m_init_success)
		{
			std::cout << "(Line) ERROR: unable to draw due to unsuccessful initialization" << std::endl;
			return;
		}

		glLineWidth(2);
		m_shader->Activate();
		m_vao->Bind();
		glm::vec4 color = glm::vec4(1, 1, 1, 1);
		m_shader->SetUniformVec4("line_color", color);

		glDrawArrays(GL_LINES, 0, 2);
	}

	bool Line::Init()
	{
		if (!Entity::Init())
			return false;

		float position_final_start_x = map(m_start.x, 0, 800, -1, 1);
		float position_final_start_y = map(m_start.y, 0, 800, -1, 1);

		float position_final_end_x = map(m_end.x, 0, 800, -1, 1);
		float position_final_end_y = map(m_end.y, 0, 800, -1, 1);

		m_start.x = position_final_start_x;
		m_start.y = position_final_start_y;

		m_end.x = position_final_end_x;
		m_end.y = position_final_end_y;

		m_vertex_data_list =
		{
			m_start.x, m_start.y, m_start.z,

			m_end.x, m_end.y, m_end.z
		};

		m_vertices_ptr = m_vertex_data_list.data();

		m_vao = new VertexArray();
		m_vao->Bind();

		m_vbo = new VertexBuffer(m_vertices_ptr, sizeof(GLfloat) * m_vertex_data_list.size());

		m_vao->LinkAttrib(*m_vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

		m_vao->Unbind();
		m_vbo->Unbind();

		return true;
	}

	void Line::LoadDefaultShader()
	{
		m_shader = new Shader("basicLine.vert", "basicLine.frag");
		m_shader->Activate();
		glm::vec4 color = glm::vec4(1, 1, 1, 1);
		m_shader->SetUniformVec4("line_color", color);
	}
}