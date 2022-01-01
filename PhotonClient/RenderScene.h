#pragma once
#include "PhotonRenderer.h"
#include "Cube.h"
class RenderScene : public Scene
{
public:
	RenderScene();
	void Render() override;
	void OnCreate() override;
	void Dispose() override;
public:
	Photon::Cube* test_obj;
	Photon::Cube* light_cube;
	Camera* cam;
	Shader* light_shader;
};

