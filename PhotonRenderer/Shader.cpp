#include "Shader.h"
#include <Windows.h>

std::string get_file_contents(const char* file_name)
{
	std::ifstream in(file_name, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vert_path, const char* frag_path)
{
	std::string vert_code = get_file_contents(vert_path);
	const char* vert_source = vert_code.c_str();
	std::string frag_code = get_file_contents(frag_path).c_str();
	const char* frag_source = frag_code.c_str();

	//Create and compile vertext shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vert_source, NULL);
	glCompileShader(vertexShader);

	if (HasCompileError(vertexShader, GL_VERTEX_SHADER))
		return;

	//Create and compile fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &frag_source, NULL);
	glCompileShader(fragmentShader);

	if (HasCompileError(fragmentShader, GL_FRAGMENT_SHADER))
		return;

	//Create the shader program
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	//Link the program
	glLinkProgram(ID);

	//Delete shaders because these are already attached to the program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

bool Shader::HasCompileError(GLuint id, unsigned int type)
{
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		//allocate to stack dynamically...
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "ERROR: fail to compile "
			<< (type == GL_VERTEX_SHADER ? "vertex shader" : "fragment shader ")
			<< message << std::endl;
		glDeleteShader(id);
		return true;
	}
	return false;
}


void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}

void Shader::SetFloat(const std::string& name, float i)
{
	int location = GetUniformLocation(name);
	glUniform1f(location, i);
}

void Shader::SetInt(const std::string& name, int i)
{
	int location = GetUniformLocation(name);
	glUniform1i(location, i);
}

void Shader::SetUniformMat4(const std::string& name, glm::mat4 matrix)
{
	int location = GetUniformLocation(name);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	int location = GetUniformLocation(name);
	glUniform4f(location, v0, v1, v2, v3);
}

void Shader::SetUniformVec4(const std::string& name, glm::vec4 v)
{
	int location = GetUniformLocation(name);
	glUniform4f(location, v.x, v.y, v.z, v.w);
}

void Shader::SetUniformVec3(const std::string& name, glm::vec3 v)
{
	int location = GetUniformLocation(name);
	glUniform3f(location, v.x, v.y, v.z);
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_uniform_location_cache.find(name) != m_uniform_location_cache.end())
		return m_uniform_location_cache[name];
	int location = glGetUniformLocation(ID, name.c_str());
	if(location != -1)
		std::cout << "Warning! : Uniform variable " << name << " does not exist." << std::endl;
	m_uniform_location_cache[name] = location;
	return location;
}
