#include <glm\glm.hpp>
class Vertex
{
public:
	Vertex(glm::vec3 position) : Position(position) {};
	Vertex();
public:
	glm::vec2 TextureCord;
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec4 Colour = glm::vec4(1, 1, 1, 1);
};


