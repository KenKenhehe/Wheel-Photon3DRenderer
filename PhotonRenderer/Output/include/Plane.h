#include "Texture.h"
#include <stb\stb_image.h> 
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Entity.h"

class PHOTON_API Plane
{
public:
	Plane(int width, int height);
	void Draw(float x, float y, float z);

private:
	int m_width;
	int m_height;
	/*float* m_vertices;
	Shader shader;*/
};

