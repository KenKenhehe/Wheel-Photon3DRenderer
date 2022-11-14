#pragma once
#ifndef LIGHT_H
#define LIGHT_H

#include "Entity.h"
namespace Photon {
	class Light : public Entity
	{
	public:
		Light(glm::vec3 position);
		glm::vec3 GetPosition() { return m_position; }
	};
}

#endif 

