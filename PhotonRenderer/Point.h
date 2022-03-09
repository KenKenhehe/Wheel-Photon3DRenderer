#pragma once
#include "Entity.h"

namespace Photon {
	class PHOTON_API Point : public Entity
	{
	public:
		Point(glm::vec3 position);
		Point(glm::vec2 position);
		void Draw(Camera* cam = nullptr) override;
	private:
		bool Init() override;

		void LoadDefaultShader();

		Shader* m_shader;
	};
}

