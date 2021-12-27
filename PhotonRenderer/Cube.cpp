#include "Cube.h"

Cube::Cube():
	m_basic_shader("basic.vert", "basic.frag"), 
	m_position(glm::vec3(0,0,0)), 
	m_scale(glm::vec3(1,1,1))
{	
	Init();
}

Cube::Cube(float scale, glm::vec3 position):
	m_basic_shader("basic.vert", "basic.frag"),
	m_position(position),
	m_scale(glm::vec3(scale, scale, scale))
{
	Init();
}

Cube::Cube(float scale, float posistion_x, float position_y, float position_z):
	m_basic_shader("basic.vert", "basic.frag"),
	m_position(glm::vec3(posistion_x, position_y, position_z)),
	m_scale(glm::vec3(scale, scale, scale))
{
	Init();
}

Cube::Cube(float scale, float posistion_x, float position_y, float position_z, Shader& shader):
	m_basic_shader(shader),
	m_position(glm::vec3(posistion_x, position_y, position_z)),
	m_scale(glm::vec3(scale, scale, scale))
{
	Init();
}

Cube::Cube(float width, float height, float depth, glm::vec3 position):
	m_basic_shader("basic.vert", "basic.frag"),
	m_position(position),
	m_scale(glm::vec3(width, height, depth))
{
	Init();
}

Cube::Cube(float width, float height, float depth, glm::vec3 position, Shader& shader):
	m_basic_shader(shader),
	m_position(position),
	m_scale(glm::vec3(width, height, depth))
{
	Init();
}

Cube::Cube(float width, float height, float depth, float position_x, float position_y, float position_z) :
	m_basic_shader("basic.vert", "basic.frag"),
	m_position(glm::vec3(position_x, position_y, position_z)),
	m_scale(glm::vec3(width, height, depth))
{
	Init();
}

Cube::Cube(float width, float height, float depth, float position_x, float position_y, float position_z, Shader& shader) :
	m_basic_shader(shader),
	m_position(glm::vec3(position_x, position_y, position_z)),
	m_scale(glm::vec3(width, height, depth))
{
	Init();
}




void Cube::Draw(Camera& camera)
{
	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
	//glm::mat4 model = glm::mat4(1.0);
	glm::vec4 color = glm::vec4(1, 1, 1, 1);
	//model = glm::translate(model, pos);

	m_basic_shader.Activate();
	camera.SetUniform(m_basic_shader, "camMatrix");
	m_basic_shader.SetUniformMat4("model", m_model);
	m_basic_shader.SetUniformVec4("Color", color);

	m_vao.Bind();
	glDrawElements(GL_TRIANGLES, sizeof(m_indices) / sizeof(int), GL_UNSIGNED_INT, 0);
}

void Cube::Dispose()
{
	m_vao.Delete();
}

void Cube::Init()
{
	m_vertices_list =
	{
		-(m_scale.x / 2), -(m_scale.y / 2),   m_scale.z / 2,
		-(m_scale.x / 2), -(m_scale.y / 2), -(m_scale.z / 2),
		  m_scale.x / 2,  -(m_scale.y / 2), -(m_scale.z / 2),
		  m_scale.x / 2,  -(m_scale.y / 2),   m_scale.z / 2,
		-(m_scale.x / 2),   m_scale.y / 2,    m_scale.z / 2,
		-(m_scale.x / 2),   m_scale.y / 2,  -(m_scale.z / 2),
		  m_scale.x / 2,    m_scale.y / 2,  -(m_scale.z / 2),
		  m_scale.x / 2,    m_scale.y / 2,    m_scale.z / 2,
	};

	m_indices_list =
	{
		0, 1, 2,
		0, 2, 3,
		0, 4, 7,
		0, 7, 3,
		3, 7, 6,
		3, 6, 2,
		2, 6, 5,
		2, 5, 1,
		1, 5, 4,
		1, 4, 0,
		4, 5, 6,
		4, 6, 7
	};

	m_vertices_ptr = m_vertices_list.data();
	m_indices_ptr = m_indices_list.data();

	m_vao.Bind();
	int size = sizeof(GLfloat) * m_vertices_list.size();

	VertexBuffer vbo(m_vertices_ptr, sizeof(GLfloat) * m_vertices_list.size());
	IndexBuffer ibo(m_indices_ptr, sizeof(GLuint) * m_indices_list.size());
	m_vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	m_vao.Unbind();
	vbo.Unbind();
	ibo.Unbind();

	m_model = glm::mat4(1.0);
	glm::vec4 color = glm::vec4(1, 1, 1, 1);
	m_model = glm::translate(m_model, m_position);

	m_basic_shader.Activate();
	m_basic_shader.SetUniformMat4("model", m_model);
	m_basic_shader.SetUniformVec4("Color", color);
}


