#include "Cube.h"

namespace Photon
{
	Cube::Cube() :
		Entity(glm::vec3(0, 0, 0)),
		m_scale(glm::vec3(1, 1, 1))
	{
		if (Init() == true)
			LoadDefaultShader();
	}

	Cube::Cube(float scale, glm::vec3 position) :
		Entity(position),
		m_scale(glm::vec3(scale, scale, scale))
	{
		if (Init() == true)
			LoadDefaultShader();
	}

	Cube::Cube(float scale, float posistion_x, float position_y, float position_z) :
		Entity(glm::vec3(posistion_x, position_y, position_z)),
		m_scale(glm::vec3(scale, scale, scale))
	{
		if (Init() == true)
			LoadDefaultShader();
	}



	Cube::Cube(float width, float height, float depth, glm::vec3 position) :
		Entity(position),
		m_scale(glm::vec3(width, height, depth))
	{
		if (Init() == true)
			LoadDefaultShader();
	}


	Cube::Cube(float width, float height, float depth, float position_x, float position_y, float position_z) :
		Entity(glm::vec3(position_x, position_y, position_z)),
		m_scale(glm::vec3(width, height, depth))
	{
		if (Init() == true)
			LoadDefaultShader();
	}


	Cube::Cube(glm::vec3 scale, glm::vec3 position) :
		Entity(position),
		m_scale(scale)
	{
		if(Init() == true)
			LoadDefaultShader();
	}


	Cube::Cube(glm::vec3 scale, float position_x, float position_y, float position_z) :
		Entity(glm::vec3(position_x, position_y, position_z)),
		m_scale(scale)
	{
		if (Init() == true)
			LoadDefaultShader();
	}

	void Cube::Draw(Camera* camera)
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

		if (m_texure != nullptr)
		{
			m_texure->Bind();
		}

		if (camera != nullptr)
		{
			camera->SetUniform(*m_shader, "camMatrix");
		}
		m_shader->SetUniformMat4("model", m_model);

		m_vao->Bind();
		glDrawElements(GL_TRIANGLES, sizeof(GLuint) * m_indices_list.size() / sizeof(int), GL_UNSIGNED_INT, 0);
	}

	void Cube::Dispose()
	{
		m_vao->Delete();
		m_vbo->Delete();
		m_ibo->Delete();
		delete m_ibo;
		delete m_vbo;
		delete m_shader;

		if (m_texure != nullptr)
		{
			m_texure->Delete();
			delete m_texure;
		}
	}

	bool Cube::Init()
	{
		if (!Entity::Init())
			return false;

		m_vertex_data_list =
		{
			//					Coordinate					//
			-(m_scale.x / 2), -(m_scale.y / 2),   m_scale.z / 2,  // front bottom left 0
			 //Color
			  1,1,1,
			  //text coord
			  0,0,
			  //normal
			  0, 0, 1,

			  m_scale.x / 2, -(m_scale.y / 2), m_scale.z / 2, // front bottom right 1
			  //Color
			  1,1,1,
			  //TODO: text coord
			  1,0,
			  //TODO: normal
			  0, 0, 1,

			  -(m_scale.x / 2),  m_scale.y / 2, m_scale.z / 2, // front up left 2
			  //TODO: Color
			  1,1,1,
			  //TODO: text coord
			  0,1,
			  //TODO: normal
			  0, 0, 1,

			  m_scale.x / 2,  m_scale.y / 2,   m_scale.z / 2,  // front up right 3
			  //Color
			  1,1,1,
			  //text coord
			  1,1,
			  //normal
			  0, 0, 1,

			-(m_scale.x / 2),   m_scale.y / 2,    -(m_scale.z / 2),  // back up left 4
			  //Color
			  1,1,1,
			  //text coord
			  0,1,
			  //normal
			  0, 0, -1,

			  m_scale.x / 2,   m_scale.y / 2,  -(m_scale.z / 2), // back up right 5
			  //Color
			  1,1,1,
			  //text coord
			  1,1,
			  //normal
			  0, 0, -1,

			  m_scale.x / 2,    -(m_scale.y / 2),  -(m_scale.z / 2), // back bottom right 6
			  //Color
			  1,1,1,
			  //text coord
			  1,0,
			  //normal
			  0, 0, -1,

			  -(m_scale.x / 2),    -(m_scale.y / 2),    -(m_scale.z / 2),  // back bottom left 7
			  //Color
			  1,1,1,
			  //text coord
			  0,0,
			  //normal
			  0, 0, -1,

			  -(m_scale.x / 2), m_scale.y / 2, m_scale.z / 2, //left front up  8
			  1,1,1,
			  //Texture:
			  1,1,
			  //Normal:
			  -1, 0, 0,

			  -(m_scale.x / 2), -(m_scale.y / 2), m_scale.z / 2, //left front down 9
			  1,1,1,
			  //Texture:
			  1,0,
			  //Normal:
			 -1, 0, 0,

			-(m_scale.x / 2), m_scale.y / 2, -(m_scale.z / 2), //left back up 10
			  1,1,1,
			  //Texture:
			  0,1,
			  //Normal:
			  -1, 0, 0,

			-(m_scale.x / 2), -(m_scale.y / 2), -(m_scale.z / 2), //left back down 11
			  1,1,1,
			  //Texture:
			  0,0,
			  //Normal:
			 -1, 0, 0,

			  m_scale.x / 2, m_scale.y / 2, m_scale.z / 2, //right front up  12
			  1,1,1,
			  //Texture:
			  0,1,
			  //Normal:
			  1, 0, 0,

			  m_scale.x / 2, -(m_scale.y / 2), m_scale.z / 2, //right front down 13
			  1,1,1,
			  //Texture:
			  0,0,
			  //Normal:
			  1, 0, 0,

			  m_scale.x / 2, m_scale.y / 2, -(m_scale.z / 2), //right back up 14
			  1,1,1,
			  //Texture:
			  1,1,
			  //Normal:
			  1, 0, 0,

			  m_scale.x / 2, -(m_scale.y / 2), -(m_scale.z / 2), //right back down 15
			  1,1,1,
			  //Texture:
			  1,0,
			  //Normal:
			  1, 0, 0,

			  -(m_scale.x / 2), m_scale.y / 2, m_scale.z / 2, //up left front 16
			  1,1,1,
			  //Texture:
			  0,0,
			  //Normal:
			  0, 1, 0,

			  m_scale.x / 2, m_scale.y / 2, m_scale.z / 2, //up right front 17
			  1, 1, 1,
			  //Texture:
			  1, 0,
			  //Normal:
			  0, 1, 0,

			  -(m_scale.x / 2), m_scale.y / 2, -(m_scale.z / 2), //up left back 18
			  1,1,1,
			  //Texture:
			  0,1,
			  //Normal:
			  0, 1, 0,

			  m_scale.x / 2, m_scale.y / 2, -(m_scale.z / 2), //up right back 19
			  1,1,1,
			  //Texture:
			  1,1,
			  //Normal:
			  0, 1, 0,

			  -(m_scale.x / 2), -(m_scale.y / 2), m_scale.z / 2, //bottom left front 20
			  1, 1, 1,
			  //Texture:
			  0, 1,
			  //Normal:
			  0, -1, 0,

			  m_scale.x / 2, -(m_scale.y / 2), m_scale.z / 2, //bottom right front 21
			  1, 1, 1,
			  //Texture:
			  1, 1,
			  //Normal:
			  0, -1, 0,

			  -(m_scale.x / 2), -(m_scale.y / 2), -(m_scale.z / 2), //bottom left back 22
			  1, 1, 1,
			  //Texture:
			  0, 0,
			  //Normal:
			  0, -1, 0,

			  m_scale.x / 2, -(m_scale.y / 2), -(m_scale.z / 2), //bottom right back 23
			  1, 1, 1,
			  //Texture:
			  1, 0,
			  //Normal:
			  0, -1, 0,
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

		std::cout << "Test map: " << map(700, 0, 800, -1, 1) << std::endl;

		m_vertices_ptr = m_vertex_data_list.data();
		m_indices_ptr = m_indices_list.data();



		m_vao = new VertexArray();
		m_vao->Bind();
		int size = sizeof(GLfloat) * m_vertex_data_list.size();

		m_vbo = new VertexBuffer(m_vertices_ptr, sizeof(GLfloat) * m_vertex_data_list.size());
		m_ibo = new IndexBuffer(m_indices_ptr, sizeof(GLuint) * m_indices_list.size());

		m_vao->LinkAttrib(*m_vbo, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
		m_vao->LinkAttrib(*m_vbo, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
		m_vao->LinkAttrib(*m_vbo, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
		m_vao->LinkAttrib(*m_vbo, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

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

	void Cube::LoadTexture(const std::string& file_path)
	{
		m_texure = new Texture(file_path.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
		m_shader->Activate();
		m_shader->SetInt("tex0", 0);
		m_shader->SetUniformVec4("Color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		m_texure->Unbind();
	}

	void Cube::LoadDefaultShader()
	{
		m_shader = new Shader("basic.vert", "basic.frag");
		m_shader->Activate();
		glm::vec4 color = glm::vec4(1, 1, 1, 1);
		m_shader->SetUniformMat4("model", m_model);
		m_shader->SetUniformVec4("Color", color);
	}

	void Cube::LoadShader(Shader& shader)
	{
		m_shader = &shader;
		m_shader->Activate();
	}
}