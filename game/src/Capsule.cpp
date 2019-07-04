#include "Capsule.h"

void Capsule::init(b2World* t_world, const glm::vec2& t_position, const glm::vec2& t_dimensions, float t_density, float t_friction, bool t_fixedRotation) 
{
	m_dimensions = t_dimensions;

	// Make the body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(t_position.x, t_position.y);
	bodyDef.fixedRotation = t_fixedRotation;
	m_body = t_world->CreateBody(&bodyDef);

	// Create the box
	b2PolygonShape boxShape;
	boxShape.SetAsBox(t_dimensions.x / 2.0f, (t_dimensions.y - t_dimensions.x) / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = t_density;
	fixtureDef.friction = t_friction;
	m_fixtures[0] = m_body->CreateFixture(&fixtureDef);

	// Create the circles
	b2CircleShape circleShape;
	circleShape.m_radius = t_dimensions.x / 2.0f;

	b2FixtureDef circleDef;
	circleDef.shape = &circleShape;
	circleDef.density = t_density;
	circleDef.friction = t_friction;

	// Bottom circle
	circleShape.m_p.Set(0.0f, (-m_dimensions.y + t_dimensions.x) / 2.0f);
	m_fixtures[1] = m_body->CreateFixture(&circleDef);

	// Top Circle
	circleShape.m_p.Set(0.0f, (m_dimensions.y - t_dimensions.x) / 2.0f);
	m_fixtures[1] = m_body->CreateFixture(&circleDef);
}

void Capsule::destroy(b2World* t_world) 
{
	if (m_body) 
	{
		t_world->DestroyBody(m_body);
		m_body = nullptr;
	}
}
