#include "Entity.h"

Photon::PhotonApplication* Photon::PhotonApplication::instance;

bool Photon::Entity::Init()
{
	if (Photon::PhotonApplication::instance == nullptr)
	{
		m_init_success = false;
		std::cout << "ERROR: Photon window has not been created yet, can not initialize Entity" << std::endl;
		return false;
	}
	m_init_success = true;
	return m_init_success;
}
