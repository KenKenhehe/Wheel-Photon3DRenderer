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

	Cube::~Cube()
	{
		delete m_shader;
		if (m_texture != nullptr) {
			delete m_texture;
		}
		delete m_ibo;
		delete m_vao;
		delete m_vbo;
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

		if (m_texture != nullptr)
		{
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

	void Cube::Dispose()
	{
		m_vao->Delete();
		m_vbo->Delete();
		m_ibo->Delete();
		delete m_ibo;
		delete m_vbo;
		delete m_shader;

		if (m_texture != nullptr)
		{
			m_texture->Delete();
			delete m_texture;
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
			 
			  //text coord
			  0,0,
			  //normal
			  0, 0, 1,

			  m_scale.x / 2, -(m_scale.y / 2), m_scale.z / 2, // front bottom right 1

			  //TODO: text coord
			  1,0,
			  //TODO: normal
			  0, 0, 1,

			  -(m_scale.x / 2),  m_scale.y / 2, m_scale.z / 2, // front up left 2
	
			  //TODO: text coord
			  0,1,
			  //TODO: normal
			  0, 0, 1,

			  m_scale.x / 2,  m_scale.y / 2,   m_scale.z / 2,  // front up right 3

			  //text coord
			  1,1,
			  //normal
			  0, 0, 1,

			-(m_scale.x / 2),   m_scale.y / 2,    -(m_scale.z / 2),  // back up left 4
			 
			  //text coord
			  0,1,
			  //normal
			  0, 0, -1,

			  m_scale.x / 2,   m_scale.y / 2,  -(m_scale.z / 2), // back up right 5
			  
			  //text coord
			  1,1,
			  //normal
			  0, 0, -1,

			  m_scale.x / 2,    -(m_scale.y / 2),  -(m_scale.z / 2), // back bottom right 6
			  
			  //text coord
			  1,0,
			  //normal
			  0, 0, -1,

			  -(m_scale.x / 2),    -(m_scale.y / 2),    -(m_scale.z / 2),  // back bottom left 7
			  
			  //text coord
			  0,0,
			  //normal
			  0, 0, -1,

			  -(m_scale.x / 2), m_scale.y / 2, m_scale.z / 2, //left front up  8
			  
			  //Texture:
			  1,1,
			  //Normal:
			  -1, 0, 0,

			  -(m_scale.x / 2), -(m_scale.y / 2), m_scale.z / 2, //left front down 9
			  
			  //Texture:
			  1,0,
			  //Normal:
			 -1, 0, 0,

			-(m_scale.x / 2), m_scale.y / 2, -(m_scale.z / 2), //left back up 10
			  
			  //Texture:
			  0,1,
			  //Normal:
			  -1, 0, 0,

			-(m_scale.x / 2), -(m_scale.y / 2), -(m_scale.z / 2), //left back down 11
			  
			  //Texture:
			  0,0,
			  //Normal:
			 -1, 0, 0,

			  m_scale.x / 2, m_scale.y / 2, m_scale.z / 2, //right front up  12
			  
			  //Texture:
			  0,1,
			  //Normal:
			  1, 0, 0,

			  m_scale.x / 2, -(m_scale.y / 2), m_scale.z / 2, //right front down 13
			  
			  //Texture:
			  0,0,
			  //Normal:
			  1, 0, 0,

			  m_scale.x / 2, m_scale.y / 2, -(m_scale.z / 2), //right back up 14
			  
			  //Texture:
			  1,1,
			  //Normal:
			  1, 0, 0,

			  m_scale.x / 2, -(m_scale.y / 2), -(m_scale.z / 2), //right back down 15
			  
			  //Texture:
			  1,0,
			  //Normal:
			  1, 0, 0,

			  -(m_scale.x / 2), m_scale.y / 2, m_scale.z / 2, //up left front 16
			  
			  //Texture:
			  0,0,
			  //Normal:
			  0, 1, 0,

			  m_scale.x / 2, m_scale.y / 2, m_scale.z / 2, //up right front 17
			  
			  //Texture:
			  1, 0,
			  //Normal:
			  0, 1, 0,

			  -(m_scale.x / 2), m_scale.y / 2, -(m_scale.z / 2), //up left back 18
			  
			  //Texture:
			  0,1,
			  //Normal:
			  0, 1, 0,

			  m_scale.x / 2, m_scale.y / 2, -(m_scale.z / 2), //up right back 19
			  
			  //Texture:
			  1,1,
			  //Normal:
			  0, 1, 0,

			  -(m_scale.x / 2), -(m_scale.y / 2), m_scale.z / 2, //bottom left front 20
			  
			  //Texture:
			  0, 1,
			  //Normal:
			  0, -1, 0,

			  m_scale.x / 2, -(m_scale.y / 2), m_scale.z / 2, //bottom right front 21
			  
			  //Texture:
			  1, 1,
			  //Normal:
			  0, -1, 0,

			  -(m_scale.x / 2), -(m_scale.y / 2), -(m_scale.z / 2), //bottom left back 22
			  
			  //Texture:
			  0, 0,
			  //Normal:
			  0, -1, 0,

			  m_scale.x / 2, -(m_scale.y / 2), -(m_scale.z / 2), //bottom right back 23
			  
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
		/*m_vao->LinkAttrib(*m_vbo, 3, 3, GL_FLOAT, 8 * sizeof(float), (void*)(8 * sizeof(float)));*/

		m_vao->Unbind();
		m_vbo->Unbind();
		m_ibo->Unbind();

		m_model = glm::mat4(1.0);
		
		int global_width = PhotonApplication::instance->GetConfig().width;
		int global_height = PhotonApplication::instance->GetConfig().height;

		float position_final_x = map(m_position.x, 0, global_width, -1, 1);
		float position_final_y = map(m_position.y, 0, global_height, -1, 1);
		m_position.x = position_final_x;
		m_position.y = position_final_y;
		m_model = glm::translate(m_model, m_position);

		return true;
	}

	void Cube::LoadTexture(const std::string& file_path)
	{
		m_texture = new Texture(file_path.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
		m_shader = new Shader("basic.vert", "basic_texture.frag");
		m_shader->Activate();
		m_shader->SetUniformMat4("model", m_model);
		glm::vec4 objectColor = glm::vec4(1, 1, 1, 1);
		m_shader->SetUniformVec4("objectColor", objectColor);
		m_shader->SetInt("tex0", 0); 
	}

	void Cube::LoadDefaultShader()
	{
		m_shader = new Shader("basic_model.vert", "material_test.frag");
		m_shader->Activate();
		m_shader->SetUniformMat4("model", m_model);
		glm::vec4 objectColor = glm::vec4(1, 1, 1, 1);
		m_shader->SetUniformVec4("objectColor", objectColor);
		m_material.ambient = glm::vec3(0.6f);
		m_material.diffuse = glm::vec3(1);
		m_material.specular = glm::vec3(1);
		m_material.shininess = 8;

		m_shader->SetUniformVec3("material.ambient", m_material.ambient);
		m_shader->SetUniformVec3("material.diffuse", m_material.diffuse);
		m_shader->SetUniformVec3("material.specular", m_material.specular);
		m_shader->SetFloat("material.shininess", m_material.shininess);
	}

	void Cube::LoadShader(Shader* shader)
	{
		m_shader = shader;
		m_shader->Activate();
	}
	void Cube::SetMaterial(const Material& material)
	{
		m_material = material;
		m_shader->SetUniformVec3("material.ambient", m_material.ambient);
		m_shader->SetUniformVec3("material.diffuse", m_material.diffuse);
		m_shader->SetUniformVec3("material.specular", m_material.specular);
		m_shader->SetFloat("material.shininess", m_material.shininess);
	}
}