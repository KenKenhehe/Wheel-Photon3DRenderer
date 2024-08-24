#include "RenderScene.h"

#include "Cube.h"
#include "Plane.h"
#include "PointLight.h"
#include "Model.h"
#include "FPSCamera.h"
#include "InputManager.h"
#include "TankGameCamera.h"
namespace Photon 
{
	void RenderScene::Update(float delta_time)
	{
		InputManager::Instance().Update();
		/*cam->HandleInput();
		cam->Update();*/

		/*if (InputManager::Instance().GetKey(KeyCode::Up, KeyAction::Pressed))
		{
			pl->Translate(glm::vec3(0, 0, -moveSpeed) * delta_time);
		}
		if (InputManager::Instance().GetKey(KeyCode::Down, KeyAction::Pressed))
		{
			pl->Translate(glm::vec3(0, 0, moveSpeed) * delta_time);
		}
		if (InputManager::Instance().GetKey(KeyCode::Left, KeyAction::Pressed))
		{
			pl->Translate(glm::vec3(-moveSpeed, 0, 0) * delta_time);
		}
		if (InputManager::Instance().GetKey(KeyCode::Right, KeyAction::Pressed))
		{
			pl->Translate(glm::vec3(moveSpeed, 0, 0) * delta_time);
		}
		if (InputManager::Instance().GetKey(KeyCode::E, KeyAction::Pressed))
		{
			pl->Translate(glm::vec3(0, moveSpeed, 0) * delta_time);
		}
		if (InputManager::Instance().GetKey(KeyCode::Q, KeyAction::Pressed))
		{
			pl->Translate(glm::vec3(0, -moveSpeed, 0) * delta_time);
		}*/
		
		if (InputManager::Instance().GetMouseButtonDown(MouseKey::LeftMouseButton)) {
			std::cout << "Left key Pressed, fire\n";
		}

		if (InputManager::Instance().GetKey(KeyCode::W, KeyAction::Pressed))
		{
			test_obj->Translate(glm::vec3(0, 0, moveSpeed) * delta_time);
		}

		if (InputManager::Instance().GetKey(KeyCode::S, KeyAction::Pressed))
		{
			test_obj->Translate(glm::vec3(0, 0, -moveSpeed) * delta_time);
		}

		if (InputManager::Instance().GetKey(KeyCode::A, KeyAction::Pressed))
		{
			test_obj->Rotate(glm::vec3(0, delta_time * 45, 0));
		}

		if (InputManager::Instance().GetKey(KeyCode::D, KeyAction::Pressed))
		{
			test_obj->Rotate(glm::vec3(0, -delta_time * 45, 0));
		}
		//game_cam->HandleInput(delta_time);
		game_cam->SetPosition(test_obj->GetPosition() - glm::vec3(0, -7, 10));

		pl->SetPosition(game_cam->Position());
		//std::cout << "rotation: X: " << game_cam->Rotation().x << ", y: " << game_cam->Rotation().y << ", Z: " << game_cam->Rotation().z << "\n";
		//std::cout << "position: X: " << game_cam->Position().x << ", y: " << game_cam->Position().y << ", Z: " << game_cam->Position().z << "\n";

	}
	void RenderScene::Render()
	{
		game_cam->Update();
		test_obj->Draw();
		pl->ApplyLighting(test_obj);
		//light_cube->Draw();

		plane->Draw();
		pl->ApplyLighting(plane);

		test_model->Draw();
		pl->ApplyLighting(test_model);

		pl->show();
		
	
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
		//input_manager = new InputManager(GetRenderer()->GetWindow());
		test_obj = new Photon::Cube(1, 1, 1, glm::vec3(800.0f, 400.0f, 0.0f));
		//TODO: change this to handle reletive path
		//test_obj->LoadTexture("D:\\_PhotonRenderer\\Photon3DRenderer\\x64\\Release\\resources\\brick.png");
		//cam = new FPSCamera(GetWidth(), GetHeight(), glm::vec3(0.0f, 0.0f, 2.0f));
		//light_shader = new Shader("light.vert", "light.frag");
		plane = new Photon::Plane(4, 4, glm::vec3(400, 0, 0));

		/*light_cube = new Photon::Cube(glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(600.0f, 500.0f, 0.0f));
		light_cube->LoadShader(*light_shader);
		light_cube->GetShader()->Activate();
		light_cube->GetShader()->SetUniformVec4("lightColor", glm::vec4(1, 1, 1, 1));*/

		pl = new Photon::PointLight(glm::vec3(600.0f, 500.0f, 0.0f), glm::vec4(1, 1, 1, 1), false);
		game_cam = new TankGameCamera(GetWidth(), GetHeight(), glm::vec3(0.0f, 200.0f, 300.0f));
		game_cam->SetRotation(glm::vec3(0.f, -0.6f, 1));
		test_model = new Photon::Model("D:\\_photonRenderer\\test_model\\backpack\\backpack.obj", glm::vec3(0.f,300.0f, 0.0f));
	}

	void RenderScene::Dispose()
	{
		//delete test_obj;
		delete cam;
		//delete light_cube;
		//delete m_line;
		//delete m_point;
		delete plane;
		delete pl;
	}

}