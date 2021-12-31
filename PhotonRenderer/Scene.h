#pragma once
#include <GLFW\glfw3.h>
class Scene
{
public:
	Scene(){}
public:
	void virtual OnCreate() {};
	void virtual Render() {};
	void virtual Dispose() {};
	void SetWindow(GLFWwindow* window) { m_current_window = window; }
	GLFWwindow* GetCurrentWindow() {return m_current_window;}

	void SetWidth(int width) { m_current_width = width; }
	void SetHeight(int height) { m_current_height = height; }

	int GetWidth() { return m_current_width; }
	int GetHeight() { return m_current_height; }
private:
	GLFWwindow* m_current_window;
	int m_current_width;
	int m_current_height;
};

