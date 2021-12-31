#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H
#include "VertexBuffer.h"
#include "Core.h"
class PHOTON_API VertexArray
{
public:
	GLuint ID;
	VertexArray();
	void LinkAttrib(VertexBuffer& vbo, GLuint layout, GLuint numComponents, 
		GLenum type, GLsizeiptr stride, void* offset);
	void Bind();
	void Unbind();
	void Delete();
};

#endif

