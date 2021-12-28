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

Cube::Cube(glm::vec3 scale, glm::vec3 position):
	m_basic_shader("basic.vert", "basic.frag"),
	m_position(position),
	m_scale(scale)
{
	Init();
}

Cube::Cube(glm::vec3 scale, glm::vec3 position, Shader& shader):
	m_basic_shader(shader),
	m_position(position),
	m_scale(scale)
{
	Init();
}

Cube::Cube(glm::vec3 scale, float position_x, float position_y, float position_z) :
	m_basic_shader("basic.vert", "basic.frag"),
	m_position(glm::vec3(position_x, position_y, position_z)),
	m_scale(scale)
{
	Init();
}

void Cube::Draw(Camera* camera)
{
	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
	//glm::mat4 model = glm::mat4(1.0);
	glm::vec4 color = glm::vec4(1, 1, 1, 1);
	//model = glm::translate(model, pos);

	m_basic_shader.Activate();

	if (m_texure != nullptr)
	{
		m_texure->Bind();
	}

	if (camera != nullptr)
	{
		camera->SetUniform(m_basic_shader, "camMatrix");
	}
	m_basic_shader.SetUniformMat4("model", m_model);

	m_vao.Bind();
	glDrawElements(GL_TRIANGLES, sizeof(m_indices) / sizeof(int), GL_UNSIGNED_INT, 0);
}

void Cube::Dispose()
{
	m_vao.Delete();
	m_vbo->Delete();
	m_ibo->Delete();
	delete m_ibo;
	delete m_vbo;

	if (m_texure != nullptr)
	{
		m_texure->Delete();
		delete m_texure;
	}
	
}

void Cube::Init()
{
	m_vertex_data_list =
	{
		//					Coordinate					//
		-(m_scale.x / 2), -(m_scale.y / 2),   m_scale.z / 2,  // front bottom left 0
		 //Color
		  1,1,1,
		  //TODO: text coord
		  0,0,
		  //TODO: normal

		  m_scale.x / 2, -(m_scale.y / 2), m_scale.z / 2, // front bottom right 1
		  //Color
		  1,1,1,
		  //TODO: text coord
		  1,0,
		  //TODO: normal

		  -(m_scale.x / 2),  m_scale.y / 2, m_scale.z / 2, // front up left 2
		  //TODO: Color
		  1,1,1,
		  //TODO: text coord
		  0,1,
		  //TODO: normal

		  m_scale.x / 2,  m_scale.y / 2,   m_scale.z / 2,  // front up right 3
		  //Color
		  1,1,1,
		  //TODO: text coord
		  1,1,
		  //TODO: normal

		-(m_scale.x / 2),   m_scale.y / 2,    -(m_scale.z / 2),  // back up left 4
		  //Color
		  1,1,1,
		  //TODO: text coord
		  0,1,
		  //TODO: normal

		  m_scale.x / 2,   m_scale.y / 2,  -(m_scale.z / 2), // back up right 5
		  //Color
		  1,1,1,
		  //TODO: text coord
		  1,1,
		  //TODO: normal

		  m_scale.x / 2,    -(m_scale.y / 2),  -(m_scale.z / 2), // back bottom right 6
		  //TODO: Color
		  1,1,1,
		  //TODO: text coord
		  1,0,
		  //TODO: normal

		  -(m_scale.x / 2),    -(m_scale.y / 2),    -(m_scale.z / 2),  // back bottom left 7
		  //TODO: Color
		  1,1,1,
		  //TODO: text coord
		  0,0,
		  //TODO: normal

		  -(m_scale.x / 2), m_scale.y / 2, m_scale.z / 2, //left front up  8
		  1,1,1,
		  //Texture:
		  1,1,

		  -(m_scale.x / 2), -(m_scale.y / 2), m_scale.z / 2, //left front down 9
		  1,1,1,
		  //Texture:
	      1,0,

		-(m_scale.x / 2), m_scale.y / 2, -(m_scale.z / 2), //left back up 10
		  1,1,1,
		  //Texture:
		  0,1,

		-(m_scale.x / 2), -(m_scale.y / 2), -(m_scale.z / 2), //left back down 11
		  1,1,1,
		  //Texture:
		  0,0,

		  m_scale.x / 2, m_scale.y / 2, m_scale.z / 2, //right front up  12
		  1,1,1,
		  //Texture:
		  0,1,

		  m_scale.x / 2, -(m_scale.y / 2), m_scale.z / 2, //right front down 13
		  1,1,1,
		  //Texture:
		  0,0,

		  m_scale.x / 2, m_scale.y / 2, -(m_scale.z / 2), //right back up 14
		  1,1,1,
		  //Texture:
		  1,1,

		  m_scale.x / 2, -(m_scale.y / 2), -(m_scale.z / 2), //right back down 15
		  1,1,1,
		  //Texture:
		  1,0,

		  -(m_scale.x / 2), m_scale.y / 2, m_scale.z / 2, //up left front 16
		  1,1,1,
		  //Texture:
		  0,0,

		  m_scale.x / 2, m_scale.y / 2, m_scale.z / 2, //up right front 17
		  1, 1, 1,
		  //Texture:
		  1, 0,
		  
		  -(m_scale.x / 2), m_scale.y / 2, -(m_scale.z / 2), //up left back 18
		  1,1,1,
		  //Texture:
		  0,1,

		  m_scale.x / 2, m_scale.y / 2, -(m_scale.z / 2), //up right back 19
		  1,1,1,
		  //Texture:
		  1,1,

		  -(m_scale.x / 2), -(m_scale.y / 2), m_scale.z / 2, //bottom left front 20
		  1, 1, 1,
		  //Texture:
		  0, 1,
		  
		  m_scale.x / 2, -(m_scale.y / 2), m_scale.z / 2, //bottom right front 21
		  1, 1, 1,
		  //Texture:
		  1, 1,
		  
		  -(m_scale.x / 2), -(m_scale.y / 2), -(m_scale.z / 2), //bottom left back 22
		  1, 1, 1,
		  //Texture:
		  0, 0,
		  
		  m_scale.x / 2, -(m_scale.y / 2), -(m_scale.z / 2), //bottom right back 23
		  1, 1, 1,
		  //Texture:
		  1, 0,
	};

	m_indices_list =
	{
		0, 1, 2,
		1, 2, 3,
		4, 5, 6,
		4, 6, 7,
		8, 9, 10,
		10, 9, 11,
		12, 13, 14, 
		13, 14, 15,
		16, 17, 18,
		18, 19, 17,
		20, 21, 22,
		22, 23, 21
	};

	m_vertices_ptr = m_vertex_data_list.data();
	m_indices_ptr = m_indices_list.data();

	m_vao.Bind();
	int size = sizeof(GLfloat) * m_vertex_data_list.size();

	m_vbo = new VertexBuffer(m_vertices_ptr, sizeof(GLfloat) * m_vertex_data_list.size());
	m_ibo = new IndexBuffer(m_indices_ptr, sizeof(GLuint) * m_indices_list.size());
	/*VertexBuffer vbo(m_vertices_ptr, sizeof(GLfloat) * m_vertex_data_list.size());
	IndexBuffer ibo(m_indices_ptr, sizeof(GLuint) * m_indices_list.size());*/
	m_vao.LinkAttrib(*m_vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	m_vao.LinkAttrib(*m_vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	m_vao.LinkAttrib(*m_vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	m_vao.Unbind();
	m_vbo->Unbind();
	m_ibo->Unbind();

	m_model = glm::mat4(1.0);
	glm::vec4 color = glm::vec4(1, 1, 1, 1);
	m_model = glm::translate(m_model, m_position);

	m_basic_shader.Activate();
	m_basic_shader.SetUniformMat4("model", m_model);
	m_basic_shader.SetUniformVec4("Color", color);
}

void Cube::LoadTexture(const std::string& file_path)
{
	m_texure = new Texture(file_path.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	m_basic_shader.Activate();
	m_basic_shader.SetInt("tex0", 0);
	m_basic_shader.SetUniformVec4("Color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	m_texure->Unbind();
}


