#pragma once
#include <GLFW\glfw3.h>
#include "InputManager.h"
namespace Photon {
	class PHOTON_API Scene
	{
	public:
		Scene() {};
	public:
		void virtual OnCreate() {};
		void virtual Render() {};
		void virtual Dispose() {};
		void SetWindow(GLFWwindow* window) { m_current_window = window; }
		GLFWwindow* GetCurrentWindow() { return m_current_window; }

		void SetInputManager(InputManager* inputManager) { m_input_manager = inputManager; }
		InputManager* GetInputManager() { return m_input_manager; }


		void SetWidth(int width) { m_current_width = width; }
		void SetHeight(int height) { m_current_height = height; }

		int GetWidth() { return m_current_width; }
		int GetHeight() { return m_current_height; }
	private:

		GLFWwindow* m_current_window = nullptr;
		int m_current_width = 0;
		int m_current_height = 0;
		InputManager* m_input_manager = nullptr;
	};

}