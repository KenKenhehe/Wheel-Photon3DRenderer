#include "VertexArray.h"


VertexArray::VertexArray()
{
	//generate 1 VAO and VBO object
	glGenVertexArrays(1, &ID);
}

void VertexArray::LinkAttrib(VertexBuffer& vbo, GLuint layout, GLuint numComponents,
	GLenum type, GLsizeiptr stride, void* offset)
{
	vbo.Bind();
	//configure vertex attribute so that openGL knows how to read in vertex data
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	//Enable the vertex attribute array so that openGl knows how to use it
	glEnableVertexAttribArray(layout);
	vbo.Unbind();
}

void VertexArray::Bind()
{
	//Make VAO the current array object by binding it
	glBindVertexArray(ID);
}

void VertexArray::Unbind()
{
	//Bind m_vao and vbo to 0 so that we don't accendentally modify the m_vao and vbo
	glBindVertexArray(0);
}

void VertexArray::Delete()
{
	glDeleteVertexArrays(1, &ID);
}
