#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
#include "Core.h"
namespace Photon {

	enum class KeyCode
	{
		A = GLFW_KEY_A,
		Up = GLFW_KEY_UP,
		Down = GLFW_KEY_DOWN,
		Left = GLFW_KEY_LEFT,
		Right = GLFW_KEY_RIGHT,
		E = GLFW_KEY_E,
		Q = GLFW_KEY_Q
	};

	enum class KeyAction
	{
		Pressed = GLFW_PRESS,
		Release = GLFW_RELEASE
	};

	class PHOTON_API InputManager
	{
	public:
		InputManager(GLFWwindow* parent_window);

		bool GetKey(KeyCode key_code, KeyAction key_action);
	private:
		GLFWwindow* m_parent_window;
	};

}