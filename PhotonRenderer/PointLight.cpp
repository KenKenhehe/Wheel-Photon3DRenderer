#include "PointLight.h"

Photon::PointLight::PointLight(glm::vec3 position, glm::vec3 light_color, bool visual) : 
	Light(position), m_light_color(light_color), m_enable_visual(visual)
{
	if (visual) 
	{
		light_visual_cube = new Cube(glm::vec3(0.1, 0.1, 0.1), position);
		Shader* light_cube_shader = new Shader("light.vert", "light.frag");
		light_visual_cube->LoadShader(light_cube_shader);
		light_visual_cube->GetShader()->SetUniformVec3("lightColor", glm::vec4(1, 1, 1, 1));
	}
}

void Photon::PointLight::ApplyLighting(Entity* entity)
{
	entity->GetShader()->Activate();
	entity->GetShader()->SetUniformVec3("lightPosition", m_position);
	entity->GetShader()->SetUniformVec3("lightColor", m_light_color);
	glm::vec3 camera_pos = entity->GetCamera() == nullptr ? glm::vec3(0, 0, 0) : entity->GetCamera()->Position();
	entity->GetShader()->SetUniformVec3("camPos", camera_pos);
}

void Photon::PointLight::show()
{
	if (m_enable_visual)
	{
		light_visual_cube->Draw();
		light_visual_cube->SetPosition(m_position);
	}
}
