#include "SphereCollision.h"

bool Photon::SphereCollision::IsOverlap(SphereCollision* other)
{
    return glm::distance(other->m_position, m_position) < m_radius;
}
