#include "Entity.h"
#include "PhotonRenderer.h"
#include "Light.h"

#include <typeinfo>
#include <iostream>

namespace Photon
{
	bool Photon::Entity::Init()
	{
		if (Photon::PhotonApplication::instance == nullptr)
		{
			m_init_success = false;
			std::cout << "ERROR: Photon window has not been created yet, can not initialize Entity" << std::endl;
			return false;
		}
		else
		{
			std::cout << "Added entity" << std::endl;
			Photon::PhotonApplication::instance->AddEntity(this);
		}
		m_init_success = true;
		return m_init_success;
	}

	void Photon::Entity::SetCamera(Camera* cam)
	{
		m_target_camera = cam;
	}
	void Entity::AddLightSource(Light* light_source)
	{
		std::cout << typeid(light_source).name() << std::endl;
 		m_light_source = light_source;
		m_shader->Activate();
		m_shader->Activate();
		m_shader->SetUniformVec3("lightPosition", light_source->GetPosition());
		m_shader->SetUniformVec4("lightColor", glm::vec4(1, 1, 1, 1));
		m_shader->SetUniformVec4("ReflectionColor", glm::vec4(1, .1, .1, 1));
	}
}
