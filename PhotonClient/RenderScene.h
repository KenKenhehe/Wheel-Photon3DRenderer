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
	class TankGameCamera;

	class RenderScene : public Scene
	{
	public:
		void Render() override;
		void OnCreate() override;
		void Dispose() override;

		void Update(float delta_time) override;

	public:
		Photon::FPSCamera* cam;
		Photon::Cube* test_obj;
		Photon::Cube* light_cube;
		Photon::Plane* plane;
		Photon::PointLight* pl;

		Photon::Model* test_model;
		InputManager* input_manager;
		TankGameCamera* game_cam;
	private:
		float moveSpeed = 5;
	};
}
