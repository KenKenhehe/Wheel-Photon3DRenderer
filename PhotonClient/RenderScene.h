#pragma once
#include "PhotonRenderer.h"
class RenderScene : public Scene
{
public:
	RenderScene();
	void Render() override;
	void OnCreate() override;
	void Dispose() override;
public:
	Cube* test_obj;
	Cube* light_cube;
	Camera* cam;
	Shader* light_shader;
};

