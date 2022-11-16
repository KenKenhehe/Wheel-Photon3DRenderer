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
	class Light;
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
		void SetCurrentLightSource(Light* light) { m_current_light_source = light; }
		GLFWwindow* GetWindow() { return m_current_window; }
		PhotonConfig GetConfig() { return m_config; }
		Camera* GetCamera() { return m_main_camera; }
	private:
		PhotonAppStatus m_current_status = PhotonAppStatus::STATUS_EMPTY;
		std::vector<Camera*> m_cameras_in_scene;
		std::vector<Entity*> m_entities;
		GLFWwindow* m_current_window = nullptr;
		Camera* m_main_camera = nullptr;

		Light* m_current_light_source = nullptr;
		PhotonConfig m_config;
	};
}
