#pragma once
#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Light.h"
#include "Cube.h"
namespace Photon
{
	class PHOTON_API PointLight : public Light
	{
	public:
		PointLight(glm::vec3 position, 
			glm::vec3 light_color = glm::vec3(1, 1, 1), bool visual = false);
	public:
		glm::vec4 GetReflectionColor() const { return m_reflection_color; }
		inline void SetReflectionColor(const glm::vec4& color) {  m_reflection_color = color; }
		void ApplyLighting(Entity* entity) override;
		void show();
	private:
		glm::vec4 m_reflection_color;
		glm::vec3 m_light_color;
		Cube* light_visual_cube = nullptr;
		bool m_enable_visual = false;
	};
}
#endif // !POINTLIGHT_H
