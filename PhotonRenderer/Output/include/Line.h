#pragma once
#include "Entity.h"
namespace Photon
{
	class PHOTON_API Line : public Entity
	{
	public:
		Line(glm::vec3 start, glm::vec3 end);
		Line(glm::vec2 start, glm::vec2 end);

		void Draw(Camera* cam = nullptr) override;
	private:
		glm::vec3 m_start;
		glm::vec3 m_end;
		Shader* m_shader;

	private:
		bool Init() override;
		void LoadDefaultShader();
	};
}

