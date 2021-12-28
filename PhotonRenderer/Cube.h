#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Camera.h"
#include "Vertex.h"

#include <stb\stb_image.h> 
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <vector>
class Cube
{
public:
	Cube();
	Cube(float scale, glm::vec3 position);
	Cube(float scale, float posistion_x, float position_y, float position_z);
	Cube(float scale, float posistion_x, float position_y, float position_z, Shader& shader);
	Cube(float width, float height, float depth, glm::vec3 position);
	Cube(float width, float height, float depth, glm::vec3 position, Shader& shader);
	Cube(float width, float height, float depth, float posistion_x, float position_y, float position_z);
	Cube(float width, float height, float depth, float posistion_x, float position_y, float position_z, Shader& shader);
	Cube(glm::vec3 scale, glm::vec3 position);
	Cube(glm::vec3 scale, glm::vec3 position, Shader& shader);
	Cube(glm::vec3 scale, float posistion_x, float position_y, float position_z);
public:
	void Draw(Camera* camera = nullptr);
	void Dispose();
	void LoadTexture(const std::string& file_path);

	Shader GetShader() { return m_shader; };
	glm::vec3 GetPosition() { return m_position; }

	void Translate(glm::vec3 translation);
private:
	void Init();
	
private:
	std::vector<Vertex> m_vertices_list;

	glm::vec3 m_position;
	glm::vec3 m_scale;
	glm::mat4 m_model;
	Shader m_shader;
	VertexArray m_vao;

	VertexBuffer* m_vbo;
	IndexBuffer* m_ibo;

	Texture* m_texure;
	std::vector<GLfloat> m_vertex_data_list;
	std::vector<GLuint> m_indices_list;

	GLfloat* m_vertices_ptr = nullptr;
	GLuint* m_indices_ptr = nullptr;

	GLfloat m_vertices[24] =
	{ //     COORDINATES     //
		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f
	};

	GLuint m_indices[36] =
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
};

