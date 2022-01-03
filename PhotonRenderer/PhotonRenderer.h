#pragma once

#include <glad\glad.h>
#include <stb\stb_image.h> 
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <iostream>
#include <vector>

#include "Core.h"
#include "Scene.h"


namespace Photon
{
	class Entity;
	class Camera;
	enum class PhotonAppStatus
	{
		STATUS_EMPTY = 0,
		STATUS_CREATE_SUCCESS = 1,
		STATUS_CREATE_FAIL = -1
	};

	struct PhotonConfig
	{
		int width;
		int height;
		const char* title;
	};
	
	class PHOTON_API PhotonApplication
	{
	public:
		PhotonApplication(Scene& mainScene, PhotonConfig config);
		static PhotonApplication* instance;
	public:
		PhotonAppStatus GetPhotonStatus() { return m_current_status; }
		void AddEntity(Entity* entity) { m_entities.emplace_back(entity); };
		void SetMainCamera(Camera* cam);
		GLFWwindow* GetWindow() { return m_current_window; }
	private:
		PhotonAppStatus m_current_status = PhotonAppStatus::STATUS_EMPTY;
		std::vector<Camera*> m_cameras_in_scene;
		std::vector<Entity*> m_entities;
		GLFWwindow* m_current_window = nullptr;
		Camera* m_main_camera = nullptr;
	};
}
