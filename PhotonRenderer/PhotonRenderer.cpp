#include "PhotonRenderer.h"
#include "Entity.h"

namespace Photon
{
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		// make sure the viewport matches the new window dimensions; note that width and 
		// height will be significantly larger than specified on retina displays.
		
		if (PhotonApplication::instance->GetCamera() != nullptr && width > 0 && height > 0) 
		{
			PhotonApplication::instance->GetCamera()->SetHeight(height);
			PhotonApplication::instance->GetCamera()->SetWidth(width);
			PhotonApplication::instance->GetCamera()->UpdateMatrix(45.0f, 0.1f, 100.0f);
		}
		else
		{
			std::cout << "Unable to resize window content\n";
		}
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
		mainScene.SetParentRenderer(this);
		mainScene.SetWindow(window);
		mainScene.SetWidth(config.width);
		mainScene.SetHeight(config.height);

		m_input_manager = new InputManager(window);

		mainScene.SetInputManager(m_input_manager);

		m_config = config;

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
			m_entities[i]->AddLightSource(m_current_light_source);
		}

		glEnable(GL_DEPTH_TEST);
		while (!glfwWindowShouldClose(window))
		{
			float start_time = glfwGetTime();
			glClearColor(.2f, .3f, .3f, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			mainScene.Render();
			glfwSwapBuffers(window);
			glfwPollEvents();

			//get delta time
			m_current_delta_time = glfwGetTime() - start_time;
			float current_fps = 1 / m_current_delta_time;
			glfwSetWindowTitle(window, std::to_string((int)current_fps).c_str());
		}
		mainScene.Dispose();

		delete m_input_manager;
	}
	void PhotonApplication::SetMainCamera(Camera* cam)
	{
		if (m_main_camera == nullptr) 
			m_main_camera = cam;
	}
}