#include "PointLight.h"

Photon::PointLight::PointLight(glm::vec3 position, glm::vec4 reflection_color) : 
	Light(position), m_reflection_color(reflection_color)
{
	
}
