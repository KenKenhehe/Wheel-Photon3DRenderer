#pragma once
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

class Plane
{
public:
	Plane(int width, int height);
	void Draw(float x, float y, float z);

private:
	int m_width;
	int m_height;


};

