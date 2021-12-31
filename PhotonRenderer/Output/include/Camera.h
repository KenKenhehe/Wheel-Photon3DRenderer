#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H
#include <glad\glad.h>
#include <glm\glm.hpp>
#include <GLFW\glfw3.h>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Shader.h"
#include "Core.h"

class PHOTON_API Camera
{
public:
	Camera(int width, int height, glm::vec3 position) :
		m_width(width), m_height(height), m_position(position)
	{
	}
	void UpdateMatrix(float FOVdeg, float near_plane, float far_plane);
	void SetUniform(Shader& shader, const std::string& uniform);
	void HandleInput(GLFWwindow* window);
public:
	void SetWidth(int width) { m_width = width; }
	void SetHeight(int height) { m_height = height; }
	void SetPosition(glm::vec3 position) { m_position = position; }
	void SetRotation(glm::vec3 rotation) { m_rotation = rotation; }

	void SetSensitivity(float s) { m_sensitivity = s; }
	void SetSpeed(float speed) { m_speed = speed; }

	glm::vec3 Position() { return m_position; }
private:
	glm::vec3 m_position;
	glm::vec3 m_rotation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 m_cam_matrix;

	//Hack
	glm::mat4 m_view_matrix;

	int m_width;
	int m_height;

	float m_speed = 0.05f;
	float m_sensitivity = 100.0f;

	bool m_first_clicked = true;
};

#endif