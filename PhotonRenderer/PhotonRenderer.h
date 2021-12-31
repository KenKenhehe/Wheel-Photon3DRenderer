#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Camera.h"
#include <stb\stb_image.h> 
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Cube.h"
//#include "Plane.h"
#include "Scene.h"
#include "Core.h"

namespace Photon
{
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

	public:
		PhotonAppStatus GetPhotonStatus() { return m_current_status; }
	private:
		PhotonAppStatus m_current_status = PhotonAppStatus::STATUS_EMPTY;
	};
}

