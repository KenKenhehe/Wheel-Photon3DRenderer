#pragma once
#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Light.h"
namespace Photon
{
	class PHOTON_API PointLight : public Light
	{
	public:
		PointLight(glm::vec3 position, glm::vec4 reflection_color = glm::vec4(1,1,1,1));
	public:
		glm::vec4 GetReflectionColor() const { return m_reflection_color; }
		inline void SetReflectionColor(const glm::vec4& color) {  m_reflection_color = color; }
	private:
		glm::vec4 m_reflection_color;
	};
}
#endif // !POINTLIGHT_H
