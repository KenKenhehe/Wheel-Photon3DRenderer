#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(GLfloat* vertices, GLsizeiptr size)
{

	glGenBuffers(1, &ID);
	//Bind(Select) the generated vertex buffer and specify this is a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	//Use the vertext data for the VBO
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}


void VertexBuffer::Bind()
{
	//Bind VBO and specify this is a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VertexBuffer::Unbind()
{		
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::Delete()
{
	glDeleteBuffers(1, &ID);
}
