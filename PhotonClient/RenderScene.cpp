#include "RenderScene.h"

RenderScene::RenderScene()
{
	
}

void RenderScene::Render()
{
	cam->HandleInput(GetCurrentWindow());
	cam->UpdateMatrix(45.0f, 0.1f, 100.0f);
	light_cube->Draw(cam);

	test_obj->Draw(cam);

	//Specular model
	//test_obj->GetShader().SetUniformVec3("lightPosition", light_cube->GetPosition());
	//test_obj->GetShader().SetUniformVec4("lightColor", glm::vec4(1, 1, 1, 1));
	//test_obj->GetShader().SetUniformVec4("ReflectionColor", glm::vec4(1, .1, .1, 1));

	//Soild Color
	test_obj->GetShader().SetUniformVec4("SolidColor", glm::vec4(1, .1, .1, 1));
}

void RenderScene::OnCreate()
{
	test_obj = new Cube(0.5f, 0.5f, 0.5f, glm::vec3(.0f, 0.0f, 0.0f));
	cam = new Camera(GetWidth(), GetHeight(), glm::vec3(0.0f, 0.0f, 2.0f));
	light_shader = new Shader("light.vert", "light.frag");

	light_cube = new Cube(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(.5f, 0.2f, 0.0f), *light_shader);
	light_cube->GetShader().Activate();
	light_cube->GetShader().SetUniformVec4("lightColor", glm::vec4(1, 1, 1, 1));
}

void RenderScene::Dispose()
{
	delete test_obj;
	delete cam;
}
