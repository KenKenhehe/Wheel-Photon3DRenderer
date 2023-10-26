#include "FPSCamera.h"
#include "InputManager.h"
Photon::FPSCamera::FPSCamera(int width, int height, glm::vec3 position): 
	Camera(width, height, position)
{

}

void Photon::FPSCamera::HandleInput()
{
	//GLFWwindow* window = Photon::PhotonApplication::instance->GetWindow();
	if (InputManager::Instance().GetKey(KeyCode::W, KeyAction::Pressed)) 
	{
		m_position += m_current_speed * m_rotation;
	}
	if (InputManager::Instance().GetKey(KeyCode::S, KeyAction::Pressed))
	{
		m_position += m_current_speed * -m_rotation;
	}
	if (InputManager::Instance().GetKey(KeyCode::A, KeyAction::Pressed))
	{
		m_position += m_current_speed * -glm::normalize(glm::cross(m_rotation, m_up));
	}
	if (InputManager::Instance().GetKey(KeyCode::D, KeyAction::Pressed))
	{
		m_position += m_current_speed * glm::normalize(glm::cross(m_rotation, m_up));
	}
	if (InputManager::Instance().GetKey(KeyCode::E, KeyAction::Pressed))
	{
		m_position += m_current_speed * m_up;
	}
	if (InputManager::Instance().GetKey(KeyCode::E, KeyAction::Pressed))
	{
		m_position += m_current_speed * -m_up;
	}
	if (InputManager::Instance().GetKey(KeyCode::LeftShift, KeyAction::Pressed))
	{
		m_current_speed = m_run_speed;
	}
	if (InputManager::Instance().GetKey(KeyCode::LeftShift, KeyAction::Release))
	{
		m_current_speed = m_walk_speed;
	}
	if (InputManager::Instance().GetMouseButton(MouseKey::LeftMouseButton, KeyAction::Pressed)) 
	{
		InputManager::Instance().SetCursorVisibility(false);
		if (m_first_clicked)
		{
			/*glfwSetCursorPos(window, (m_width / 2), (m_height / 2));*/
			m_first_clicked = false;
		}
	}

	/*if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
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
		float rot_y = m_sensitivity * (float)(mouse_x - (m_width / 2)) / m_width;

		glm::vec3 new_rotation =
			glm::rotate(m_rotation, glm::radians(-rot_x), glm::normalize(glm::cross(m_rotation, m_up)));

		if (abs(glm::angle(new_rotation, m_up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			m_rotation = new_rotation;
		}

		m_rotation = glm::rotate(m_rotation, glm::radians(-rot_y), m_up);

		glfwSetCursorPos(window, (m_width / 2), (m_height / 2));
	}*/
	//else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	//{
	//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	//	m_first_clicked = true;
	//}
}