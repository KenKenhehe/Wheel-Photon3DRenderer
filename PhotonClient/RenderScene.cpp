#include "RenderScene.h"

#include "Cube.h"
#include "Plane.h"
#include "PointLight.h"
#include "Model.h"

namespace Photon 
{
	void RenderScene::Render()
	{
		cam->HandleInput();
		cam->UpdateMatrix(45.0f, 0.1f, 100.0f);
		cam->Update();

		/*test_obj->Draw();
		pl->ApplyLighting(test_obj);*/
		//light_cube->Draw();

		//plane->Draw();
		//pl->ApplyLighting(plane);

		test_model->Draw();
		pl->ApplyLighting(test_model);

		pl->show();
		float deltaTime = GetRenderer()->GetDeltaTime();
		if (GetInputManager()->GetKey(KeyCode::Up, KeyAction::Pressed)) 
		{
			pl->Translate(glm::vec3(0, 0, -moveSpeed) * deltaTime);
		}
		if (GetInputManager()->GetKey(KeyCode::Down, KeyAction::Pressed)) 
		{
			pl->Translate(glm::vec3(0, 0, moveSpeed) * deltaTime);
		}
		if (GetInputManager()->GetKey(KeyCode::Left, KeyAction::Pressed)) 
		{
			pl->Translate(glm::vec3(-moveSpeed, 0, 0) * deltaTime);
		}
		if (GetInputManager()->GetKey(KeyCode::Right, KeyAction::Pressed)) 
		{
			pl->Translate(glm::vec3(moveSpeed, 0, 0) * deltaTime);
		}
		if (GetInputManager()->GetKey(KeyCode::E, KeyAction::Pressed)) 
		{
			pl->Translate(glm::vec3(0, moveSpeed, 0) * deltaTime);
		}
		if (GetInputManager()->GetKey(KeyCode::Q, KeyAction::Pressed)) 
		{
			pl->Translate(glm::vec3(0, -moveSpeed, 0) * deltaTime);
		}

		//pl->SetPosition(cam->Position());
		

		//std::cout << "X: " << pl->GetPosition().x  << ", y: " << pl->GetPosition().y << ", Z: " << pl->GetPosition().z << "\n";


		//pl->Translate(glm::vec3(0.01f, 0, 0));
		//pl->Translate(glm::vec3(-0.01f, 0, 0));

		//test_model->Translate(glm::vec3(0.01f, 0, 0));

		//m_point->Draw();

		////Specular model
		//test_obj->GetShader().Activate();
		//test_obj->GetShader().SetUniformVec3("lightPosition", light_cube->GetPosition());
		//test_obj->GetShader().SetUniformVec4("lightColor", glm::vec4(1, 1, 1, 1));
		//test_obj->GetShader().SetUniformVec4("ReflectionColor", glm::vec4(1, .1, .1, 1));

		//plane->GetShader().Activate();
		//plane->GetShader().SetUniformVec3("lightPosition", light_cube->GetPosition());
		//plane->GetShader().SetUniformVec4("lightColor", glm::vec4(1, 1, 1, 1));
		//plane->GetShader().SetUniformVec4("ReflectionColor", glm::vec4(.3, .3, 1, 1));

		/*cam->Update();
		cam->HandleInput(GetCurrentWindow());
		test_obj->Draw();
		test_obj->SetMatrial(MaterialPreset::SOLID_COLOR)*/


		//Soild Color(ambient?) model
		//test_obj->GetShader().SetUniformVec4("SolidColor", glm::vec4(1, .1, .1, 1));
	}

	void RenderScene::OnCreate()
	{
		//m_point = new Photon::Point(glm::vec2(600, 400));

		test_obj = new Photon::Cube(1, 1, 1, glm::vec3(800.0f, 400.0f, 0.0f));
		//TODO: change this to handle reletive path
		//test_obj->LoadTexture("D:\\_PhotonRenderer\\Photon3DRenderer\\x64\\Release\\resources\\brick.png");
		cam = new Photon::FPSCamera(GetWidth(), GetHeight(), glm::vec3(0.0f, 0.0f, 2.0f));
		//light_shader = new Shader("light.vert", "light.frag");
		//plane = new Photon::Plane(4, 4, glm::vec3(400, 0, 0));

		/*light_cube = new Photon::Cube(glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(600.0f, 500.0f, 0.0f));
		light_cube->LoadShader(*light_shader);
		light_cube->GetShader()->Activate();
		light_cube->GetShader()->SetUniformVec4("lightColor", glm::vec4(1, 1, 1, 1));*/

		pl = new Photon::PointLight(glm::vec3(600.0f, 500.0f, 0.0f), glm::vec4(1, 1, 1, 1), true);
		test_model = new Photon::Model("D:\\_photonRenderer\\test_model\\backpack\\backpack.obj", glm::vec3(0.f,300.0f, 0.0f));
	}

	void RenderScene::Dispose()
	{
		delete test_obj;
		delete cam;
		//delete light_cube;
		//delete m_line;
		delete m_point;
		delete pl;
	}
}