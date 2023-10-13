#include "InputManager.h"
namespace Photon
{
	InputManager::InputManager(GLFWwindow* parent_window) : m_parent_window(parent_window)
	{
	}

	bool InputManager::GetKey(KeyCode key_code, KeyAction key_action)
	{
		bool key_result = glfwGetKey(m_parent_window, (int)key_code) == (int)key_action;
		return key_result;
	}
}