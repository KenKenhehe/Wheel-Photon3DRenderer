#pragma once
#include "Camera.h"
namespace Photon 
{
	class FPSCamera : public Camera
	{
	public:
		FPSCamera(int width, int height, glm::vec3 position);
		void HandleInput();

	private:
		bool m_first_clicked = true;
		float m_walk_speed = 0.01f;
		float m_run_speed = 0.05f;

		float m_current_speed = 0.01f;
		float m_sensitivity = 100.0f;
	};
}

