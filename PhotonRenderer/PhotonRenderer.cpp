#include "PhotonRenderer.h"
#include "Entity.h"

namespace Photon
{
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		// make sure the viewport matches the new window dimensions; note that width and 
		// height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);
	}
	PhotonApplication::PhotonApplication(Scene& mainScene, PhotonConfig config)
	{
		instance = this;
		//Initialize GLFW
		glfwInit();

		//Tell glfw which opengl version is used
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		//using core profile(contains only modern opengl functions)
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		//Create the glfw window object
		GLFWwindow* window = glfwCreateWindow(config.width, config.height, config.title, NULL, NULL);

		if (window == NULL)
		{
			std::cout << "Window fail to create" << std::endl;
			glfwTerminate();
			m_current_status = PhotonAppStatus::STATUS_CREATE_FAIL;
		}

		mainScene.SetWindow(window);
		mainScene.SetWidth(config.width);
		mainScene.SetHeight(config.height);

		glfwMakeContextCurrent(window);
		m_current_status = PhotonAppStatus::STATUS_CREATE_SUCCESS;
		m_current_window = window;
		
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		gladLoadGL();

		glViewport(0, 0, config.width, config.height);

		glfwSwapBuffers(window);

		mainScene.OnCreate();
		for (int i = 0; i < m_entities.size(); i++)
		{
			m_entities[i]->SetCamera(m_main_camera);
		}

		glEnable(GL_DEPTH_TEST);
		while (!glfwWindowShouldClose(window))
		{
			glClearColor(.2f, .3f, .3f, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			mainScene.Render();
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		mainScene.Dispose();
	}
	void PhotonApplication::SetMainCamera(Camera* cam)
	{
		if (m_main_camera == nullptr) 
			m_main_camera = cam;
	}
}