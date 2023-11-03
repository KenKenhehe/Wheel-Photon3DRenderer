#pragma once
#include "Camera.h"
namespace Photon {
	class TankGameCamera :public Camera
	{
	public:
		TankGameCamera(int width, int height, glm::vec3 position): Camera(width, height, position){}

		void SetFollowTarget(Entity* target);
		void SetFollowTargetOffset(glm::vec3 offset);

		void HandleInput(float delta_time);
	private:
		Entity* m_follow_target = nullptr;
		glm::vec3 m_follow_target_offset = glm::vec3(0);
		float m_current_speed = 0.05f;
		bool m_first_clicked = true;
		float m_sensitivity = 100.0f;

	};
}
