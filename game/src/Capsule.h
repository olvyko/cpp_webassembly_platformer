#pragma once
#include <Box2D/Box2D.h>
#include <glm/glm.hpp>

class Capsule 
{
public:
	void init(b2World* t_world, const glm::vec2& t_position, const glm::vec2& t_dimensions, float t_density, float t_friction, bool t_fixedRotation);
	void destroy(b2World* t_world);

	b2Body* getBody() const { return m_body; }
	b2Fixture* getFixture(int t_index) const { return m_fixtures[t_index]; }
	const glm::vec2& getDimensions() const { return m_dimensions; }

private:
	b2Body* m_body = nullptr;
	b2Fixture* m_fixtures[3];
	glm::vec2 m_dimensions;
};
