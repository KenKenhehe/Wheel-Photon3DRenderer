#pragma once
#include "PhotonRenderer.h"
#include "Cube.h"
#include "Plane.h"
class RenderScene : public Scene
{
public:
	void Render() override;
	void OnCreate() override;
	void Dispose() override;
public:
	Photon::Cube* test_obj;
	Photon::Cube* light_cube;
	Photon::Plane* plane;
	Photon::Camera* cam;
	Shader* light_shader;
};

