#include "PointLight.h"

Photon::PointLight::PointLight(glm::vec3 position, glm::vec4 reflection_color, glm::vec4 light_color) : 
	Light(position), m_reflection_color(reflection_color), m_light_color(light_color)
{
	
}

void Photon::PointLight::ApplyLighting(Entity* entity)
{
	entity->GetShader()->Activate();
	entity->GetShader()->SetUniformVec3("lightPosition", m_position);
	entity->GetShader()->SetUniformVec4("lightColor", m_light_color);
	entity->GetShader()->SetUniformVec4("ReflectionColor", m_reflection_color);
	glm::vec3 camera_pos = entity->GetCamera() == nullptr ? glm::vec3(0, 0, 0) : entity->GetCamera()->Position();
	//std::cout << camera_pos.x << ", " << camera_pos.y << ", " << camera_pos.z << std::endl;
	entity->GetShader()->SetUniformVec3("camPos", camera_pos);
}
