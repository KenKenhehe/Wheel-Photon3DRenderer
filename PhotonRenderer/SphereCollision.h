#pragma once
#include "glm\glm.hpp"
#include "Entity.h"

namespace Photon 
{
	class PHOTON_API SphereCollision : public Entity
	{
	public:
		SphereCollision(glm::vec3 position, float radius) : Entity(position), m_radius(radius) {}

		bool IsOverlap(SphereCollision* other);
	private:
		float m_radius;
	};
}

