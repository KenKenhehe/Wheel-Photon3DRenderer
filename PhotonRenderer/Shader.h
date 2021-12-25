#ifndef SHADER_H
#define SHADER_H

#include<glad\glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <unordered_map>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

std::string get_file_contents(const char* file_name);

class Shader
{
private:
	std::unordered_map<std::string, int> m_uniform_location_cache;
	int GetUniformLocation(const std::string& name);
public:
	GLuint ID;
	Shader(const char* vert_path, const char* frag_path);

	void Activate();
	void Delete();
	void SetFloat(const std::string& name, float i);
	void SetInt(const std::string& name, int i);
	void SetUniformMat4(const std::string& name, glm::mat4 matrix);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformVec4(const std::string& name, glm::vec4 v);
	void SetUniformVec3(const std::string& name, glm::vec3 v);
	bool HasCompileError(GLuint id, unsigned int type);
};
#endif


