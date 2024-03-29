#include "Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	type = texType;
	//Texture
	//define width, height and color channel for the texture, and load the texture
	int widthImg, heightImg, numofColorChannel;
	//Flip the image vertically when loaded
	stbi_set_flip_vertically_on_load(true);
	unsigned char* img_bytes = stbi_load(image, &widthImg, &heightImg, &numofColorChannel, 0);

	if (img_bytes == nullptr) 
	{
		std::cout << "Load texture: " << std::string(image) << " failed.\n";
		return;
	}

	glGenTextures(1, &ID);
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	/*float color[] = { 1.0f, 1.0f, 0.2f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);*/

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, img_bytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(img_bytes);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::LinkShaderUniform(Shader& shader, const char* uniform, GLuint unit)
{
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}
