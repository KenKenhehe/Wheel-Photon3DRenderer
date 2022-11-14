#include "Light.h"

namespace Photon
{
	Photon::Light::Light(glm::vec3 position): Entity(m_position)
	{
		Photon::PhotonApplication::instance->SetCurrentLightSource(this);
	}
}
