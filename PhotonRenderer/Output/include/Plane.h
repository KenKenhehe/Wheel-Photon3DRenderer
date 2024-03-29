#ifndef PHOTON_PLANE_H
#define PHOTON_PLANE_H

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Entity.h"

namespace Photon
{
	class PHOTON_API Plane : public Entity
	{
	public:
		Plane(float width, float height, glm::vec3 position);
		void Draw();
		void LoadDefaultShader();
		void LoadShader(Shader& shader);

	private:
		bool Init() override;
	private:

		float m_width;
		float m_height;
		Texture* m_texture = nullptr;
		/*float* m_vertices;
		Shader shader;*/
	};
}

#endif // !PHOTON_PLANE_H