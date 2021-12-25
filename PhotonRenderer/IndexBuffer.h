#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <glad\glad.h>
class IndexBuffer
{
public:
	GLuint ID;
	IndexBuffer(GLuint* indices, GLsizeiptr size);
	void Bind();
	void Unbind();
	void Delete();
};

#endif

