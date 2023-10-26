#include "InputManager.h"
#include "glm\glm.hpp"

namespace Photon
{

	Photon::InputManager::InputManager(GLFWwindow* parent_window) : m_parent_window(parent_window)
	{
		m_parent_window = Photon::PhotonApplication::instance->GetWindow();
	}

	bool Photon::InputManager::GetKey(KeyCode key_code, KeyAction key_action)
	{
		bool key_result = glfwGetKey(m_parent_window, (int)key_code) == (int)key_action;
		return key_result;
	}

	bool Photon::InputManager::GetMouseButton(MouseKey mouse_key, KeyAction key_action) const
	{
		bool key_result = glfwGetMouseButton(m_parent_window, (int)mouse_key) == (int)key_action;
		return key_result;
	}

	void Photon::InputManager::SetCursorVisibility(bool visible)
	{
		if (visible)
		{
			glfwSetInputMode(m_parent_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else
		{
			glfwSetInputMode(m_parent_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		}
	}

	void Photon::InputManager::SetCursorEnable(bool enable)
	{
		if (enable)
		{
			glfwSetInputMode(m_parent_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else
		{
			glfwSetInputMode(m_parent_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}

	InputManager& InputManager::Instance()
	{
		static InputManager instance(Photon::PhotonApplication::instance->GetWindow());
		return instance;
	}

	void Photon::InputManager::UpdateCursorPosition()
	{
		glfwGetCursorPos(m_parent_window, &m_cursor_x, &m_cursor_y);
	}


}