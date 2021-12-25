#include "Camera.h"

void Camera::UpdateMatrix(float FOVdeg, float near_plane, float far_plane)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(m_position, m_position + m_rotation, m_up);
	projection = glm::perspective(glm::radians(FOVdeg), (float)(m_width / m_height), near_plane, far_plane);

	m_cam_matrix = projection * view;
}

void Camera::SetUniform(Shader& shader, const std::string& uniform)
{
	shader.SetUniformMat4(uniform, m_cam_matrix);
}

void Camera::HandleInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		m_position += m_speed * m_rotation;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		m_position += m_speed * -m_rotation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		m_position += m_speed * -glm::normalize(glm::cross(m_rotation, m_up));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		m_position += m_speed * glm::normalize(glm::cross(m_rotation, m_up));
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		m_position += m_speed * m_up;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		m_position += m_speed * -m_up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		m_speed = 0.1f;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		m_speed = 0.05f;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		if (m_first_clicked)
		{
			glfwSetCursorPos(window, (m_width / 2), (m_height / 2));
			m_first_clicked = false;
		}

		double mouse_x;
		double mouse_y;

		glfwGetCursorPos(window, &mouse_x, &mouse_y);

		float rot_x = m_sensitivity * (float)(mouse_y - (m_height / 2)) / m_height;
		float rot_y = m_sensitivity * (float)(mouse_x - (m_height / 2)) / m_height;

		glm::vec3 new_rotation = 
			glm::rotate(m_rotation, glm::radians(-rot_x), glm::normalize(glm::cross(m_rotation, m_up)));

		if (abs(glm::angle(new_rotation, m_up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			m_rotation = new_rotation;
		}

		m_rotation = glm::rotate(m_rotation, glm::radians(-rot_y), m_up);

		glfwSetCursorPos(window, (m_width / 2), (m_height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		m_first_clicked = true;
	}
}
