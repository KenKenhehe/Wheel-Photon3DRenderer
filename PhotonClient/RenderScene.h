#pragma once
#include "PhotonRenderer.h"
#include "Cube.h"
#include "Plane.h"
#include "Line.h"
class RenderScene : public Scene
{
public:
	void Render() override;
	void OnCreate() override;
	void Dispose() override;
public:
	Photon::Line* m_line;
	Photon::Camera* cam;
	Photon::Cube* test_obj;
	Photon::Cube* light_cube;
	Photon::Plane* plane;
	
	Shader* light_shader;
};

