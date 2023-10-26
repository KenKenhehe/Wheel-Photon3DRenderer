#pragma once
#include <GLFW\glfw3.h>
#include "Core.h"
namespace Photon {
	class PhotonApplication;
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

		void SetWidth(int width) { m_current_width = width; }
		void SetHeight(int height) { m_current_height = height; }
		void SetParentRenderer(PhotonApplication* parent_renderer) { m_parent_renderer = parent_renderer; }

		int GetWidth() { return m_current_width; }
		int GetHeight() { return m_current_height; }
		PhotonApplication* GetRenderer() { return m_parent_renderer;}

	private:

		GLFWwindow* m_current_window = nullptr;
		int m_current_width = 0;
		int m_current_height = 0;
		PhotonApplication* m_parent_renderer = nullptr;
	};

}