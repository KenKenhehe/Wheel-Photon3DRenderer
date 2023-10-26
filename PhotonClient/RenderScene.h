#pragma once
#include "PhotonRenderer.h"
#include "Scene.h"
#include "InputManager.h"

//#include <glad/glad.h>

namespace Photon 
{
	class Point;
	class FPSCamera;
	class Cube;
	class PointLight;
	class Model;
	class Plane;
	class Shader;

	class RenderScene : public Scene
	{
	public:
		void Render() override;
		void OnCreate() override;
		void Dispose() override;
	public:
		//Photon::Line* m_line;
		//Photon::Point* m_point;
		Photon::FPSCamera* cam;
		Photon::Cube* test_obj;
		Photon::Cube* light_cube;
		Photon::Plane* plane;
		Photon::PointLight* pl;

		Shader* light_shader;
		Photon::Model* test_model;
		InputManager* input_manager;
	private:
		float moveSpeed = 5;
	};
}
