#include "FPSCamera.h"
#include "InputManager.h"
Photon::FPSCamera::FPSCamera(int width, int height, glm::vec3 position): 
	Camera(width, height, position)
{

}

void Photon::FPSCamera::HandleInput()
{
	//GLFWwindow* window = Photon::PhotonApplication::instance->GetWindow();
	//if ( /*glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS*/)
	//{
	//	m_position += m_current_speed * m_rotation;
	//}
	//if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	//{
	//	m_position += m_current_speed * -m_rotation;
	//}
	//if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	//{
	//	m_position += m_current_speed * -glm::normalize(glm::cross(m_rotation, m_up));
	//}
	//if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	//{
	//	m_position += m_current_speed * glm::normalize(glm::cross(m_rotation, m_up));
	//}
	//if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	//{
	//	m_position += m_current_speed * m_up;
	//}
	//if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	//{
	//	m_position += m_current_speed * -m_up;
	//}
	//if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	//{
	//	m_current_speed = m_run_speed;
	//}
	//if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	//{
	//	m_current_speed = m_walk_speed;
	//}

	//if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	//{
	//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	//	if (m_first_clicked)
	//	{
	//		glfwSetCursorPos(window, (m_width / 2), (m_height / 2));
	//		m_first_clicked = false;
	//	}

	//	double mouse_x;
	//	double mouse_y;

	//	glfwGetCursorPos(window, &mouse_x, &mouse_y);

	//	float rot_x = m_sensitivity * (float)(mouse_y - (m_height / 2)) / m_height;
	//	float rot_y = m_sensitivity * (float)(mouse_x - (m_width / 2)) / m_width;

	//	glm::vec3 new_rotation =
	//		glm::rotate(m_rotation, glm::radians(-rot_x), glm::normalize(glm::cross(m_rotation, m_up)));

	//	if (abs(glm::angle(new_rotation, m_up) - glm::radians(90.0f)) <= glm::radians(85.0f))
	//	{
	//		m_rotation = new_rotation;
	//	}

	//	m_rotation = glm::rotate(m_rotation, glm::radians(-rot_y), m_up);

	//	glfwSetCursorPos(window, (m_width / 2), (m_height / 2));
	//}
	//else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	//{
	//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	//	m_first_clicked = true;
	//}
}