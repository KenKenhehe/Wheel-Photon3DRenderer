#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "Shader.h"
#include "Core.h"
#include "PhotonRenderer.h"

namespace Photon
{
	//class PHOTON_API Camera 
	//{
	//public:
	//	Camera();
	//	virtual void Update() = 0;  
	//	virtual void HandleInput() = 0;

	//private:
	//	glm::vec3 m_position;
	//	glm::vec3 m_rotation = glm::vec3(0.0f, 0.0f, -1.0f);
	//	glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);

	//	glm::mat4 m_cam_matrix;

	//	//Hack
	//	glm::mat4 m_view_matrix;

	//	int m_width;
	//	int m_height;

	//	float m_speed = 0.01f;
	//	float m_sensitivity = 100.0f;
	//	float m_fov = 45.0f;
	//	float m_near_plane = 0.1f;
	//	float m_far_plane = 100.0f;
	//};

	class PHOTON_API Camera
	{
	public:
		Camera(int width, int height, glm::vec3 position);
		void UpdateMatrix(float FOVdeg, float near_plane, float far_plane);
		void Update();
		void SetUniform(Shader& shader, const std::string& uniform);
		//void HandleInput();
	public:
		void SetWidth(int width) { m_width = width; }
		void SetHeight(int height) { m_height = height; }
		void SetPosition(glm::vec3 position) { m_position = position; }
		void SetRotation(glm::vec3 rotation) { m_rotation = rotation; }

		//void SetSensitivity(float s) { m_sensitivity = s; }
		//void SetSpeed(float speed) { m_current_speed = speed; }

		void SetFOV(float fov) { m_fov = fov; }
		void SetNearPlane(float near_plane) { m_near_plane = near_plane; }
		void SetFarPlane(float far_plane) { m_far_plane = far_plane; }

		glm::vec3 Position() { return m_position; }
	protected:
		glm::vec3 m_position;
		glm::vec3 m_rotation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::mat4 m_cam_matrix;

		//Hack
		glm::mat4 m_view_matrix;

		int m_width;
		int m_height;

		float m_fov = 45.0f;
		float m_near_plane = 0.1f;
		float m_far_plane = 100.0f;

	};
}
#endif