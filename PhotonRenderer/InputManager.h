#pragma once
#include <iostream>
#include "PhotonRenderer.h"
#include "glm/glm.hpp"

namespace Photon {

	enum class KeyCode
	{
		A = GLFW_KEY_A,
		W = GLFW_KEY_W,
		S = GLFW_KEY_S,
		D = GLFW_KEY_D,
		Up = GLFW_KEY_UP,
		Down = GLFW_KEY_DOWN,
		Left = GLFW_KEY_LEFT,
		Right = GLFW_KEY_RIGHT,
		E = GLFW_KEY_E,
		Q = GLFW_KEY_Q,
		LeftShift = GLFW_KEY_LEFT_SHIFT,
		rightShift = GLFW_KEY_RIGHT_SHIFT
	};

	enum class MouseKey
	{
		LeftMouseButton = GLFW_MOUSE_BUTTON_LEFT,
		RightMouseButton = GLFW_MOUSE_BUTTON_RIGHT,
		MiddleMouseButton = GLFW_MOUSE_BUTTON_MIDDLE
	};

	enum class KeyAction
	{
		Pressed = GLFW_PRESS,
		Release = GLFW_RELEASE
	};

	struct MousePosition 
	{
		double cursor_x;
		double cursor_y;
	};

	class PHOTON_API InputManager
	{
	public:
		InputManager(GLFWwindow* parent_window);
		
		//Keyboard-related input
		bool GetKey(KeyCode key_code, KeyAction key_action);

		//Mouse-related input
		bool GetMouseButton(MouseKey mouse_key, KeyAction key_action);
		bool GetMouseButtonDown(MouseKey mouse_key);

		void SetCursorVisibility(bool visible);
		void SetCursorEnable(bool enable);
		void SetMousePosition(double x, double y);
		
		//Call UpdateCursorPosition() first before calling GetMouseX(Y) to get the current mouse position
		double GetMouseX() const { return m_cursor_x; }

		//Call UpdateCursorPosition() first before calling GetMouseX(Y) to get the current mouse position
		double GetMouseY() const { return m_cursor_y; }

		glm::vec2 GetMousePosition();

		static InputManager& Instance();

		void UpdateCursorPosition();
		void Update();

		/*InputManager(const InputManager&) = delete;
		InputManager& operator=(const InputManager&) = delete;*/
	private:
		GLFWwindow* m_parent_window;

		//Mouse-related states
		double m_cursor_x = 0;
		double m_cursor_y = 0;

		bool hasMouseButtonPressed = false;
	};

}