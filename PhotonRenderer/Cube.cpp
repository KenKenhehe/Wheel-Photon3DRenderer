#include "Cube.h"

Cube::Cube():
	m_basic_shader("basic.vert", "basic.frag"), 
	m_position(glm::vec3(0,0,0)), 
	m_scale(glm::vec3(1,1,1))
{	
	m_vertices =
	{ //     COORDINATES     //
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f
	};

	m_vao.Bind();
	VertexBuffer vbo(m_vertices, sizeof(m_vertices));
	IndexBuffer ibo(m_indices, sizeof(m_indices));
	m_vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	m_vao.Unbind();
	vbo.Unbind();
	ibo.Unbind();

	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 model = glm::mat4(1.0);
	glm::vec4 color = glm::vec4(1, 1, 1, 1);
	model = glm::translate(model, pos);

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	m_basic_shader.Activate();
	m_basic_shader.SetUniformMat4("model", model);
	m_basic_shader.SetUniformVec4("Color", color);

}

void Cube::Draw(Camera& camera)
{
	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 model = glm::mat4(1.0);
	glm::vec4 color = glm::vec4(1, 1, 1, 1);
	model = glm::translate(model, pos);

	m_basic_shader.Activate();
	camera.SetUniform(m_basic_shader, "camMatrix");
	m_basic_shader.SetUniformMat4("model", model);
	m_basic_shader.SetUniformVec4("Color", color);

	m_vao.Bind();
	glDrawElements(GL_TRIANGLES, sizeof(m_indices) / sizeof(int), GL_UNSIGNED_INT, 0);
}

void Cube::Dispose()
{
	m_vao.Delete();
}


