#include "Entity.h"
#include "PhotonRenderer.h"

//Photon::PhotonApplication* Photon::PhotonApplication::instance;
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
}
