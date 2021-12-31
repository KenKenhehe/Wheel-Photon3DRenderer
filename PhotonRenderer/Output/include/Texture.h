#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H
#include <glad\glad.h>
#include <stb\stb_image.h>
#include "Shader.h"

#include "Core.h"

class PHOTON_API Texture
{
public:
	GLuint ID;
	GLenum type;

	Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

	void LinkShaderUniform(Shader& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();

private:

};

#endif // TEXTURE_CLASS_H

