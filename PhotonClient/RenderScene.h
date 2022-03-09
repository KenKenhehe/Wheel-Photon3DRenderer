#pragma once
#include "PhotonRenderer.h"
#include "Cube.h"
#include "Plane.h"
#include "Line.h"
#include "Point.h"
class RenderScene : public Scene
{
public:
	void Render() override;
	void OnCreate() override;
	void Dispose() override;
public:
	//Photon::Line* m_line;
	Photon::Point* m_point;
	Photon::Camera* cam;
	Photon::Cube* test_obj;
	Photon::Cube* light_cube;
	Photon::Plane* plane;
	
	Shader* light_shader;
};

