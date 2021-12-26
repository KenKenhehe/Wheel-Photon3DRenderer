#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Camera.h"
#include <stb\stb_image.h> 
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
class Cube
{
public:
	Cube();
	Cube(int width, int height, int depth, glm::vec3 position);
	Cube(int width, int height, int depth, glm::vec3 position, Shader& shader);
	Cube(int width, int height, int depth, float posistion_x, float position_y, float position_z);
	Cube(int width, int height, int depth, float posistion_x, float position_y, float position_z, Shader& shader);

public:
	void Draw(Camera& camera);
	void Dispose();

private:
	glm::vec3 m_position;
	glm::vec3 m_scale;
	Shader m_basic_shader;
	VertexArray m_vao;

	GLfloat m_vertices[24] =
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

