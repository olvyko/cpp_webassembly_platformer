#include "Box.h"

Box::Box()
{
}

Box::~Box()
{
}

void Box::init(b2World* t_world, const glm::vec2& t_position, const glm::vec2& t_dimensions, GLTexture t_texture, ColorRGBA8 t_color, bool t_fixedRotation, bool t_isDynamic, float t_angle /*= 0.0f*/, glm::vec4 t_uvRect /*= glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)*/)
{
	m_dimensions = t_dimensions;
	m_color = t_color;
	m_texture = t_texture;
	m_uvRect = t_uvRect;
	m_fixedRotation = t_fixedRotation;
	m_isDynamic = t_isDynamic;

	// Make the body
	b2BodyDef bodyDef;
	if (t_isDynamic)
	{
		bodyDef.type = b2_dynamicBody;
	}
	else 
	{
		bodyDef.type = b2_staticBody;
	}
	bodyDef.position.Set(t_position.x, t_position.y);
	bodyDef.fixedRotation = t_fixedRotation;
	bodyDef.angle = t_angle;
	m_body = t_world->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(t_dimensions.x / 2.0f, t_dimensions.y / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	m_fixture = m_body->CreateFixture(&fixtureDef);
}

void Box::destroy(b2World* t_world) 
{
	t_world->DestroyBody(m_body);
}

void Box::draw(SpriteBatch& t_spriteBatch) 
{
	glm::vec4 destRect;
	destRect.x = m_body->GetPosition().x - m_dimensions.x / 2.0f;
	destRect.y = m_body->GetPosition().y - m_dimensions.y / 2.0f;
	destRect.z = m_dimensions.x;
	destRect.w = m_dimensions.y;
	t_spriteBatch.addGlyph(destRect, m_uvRect, m_texture.id, 0.0f, m_color, m_body->GetAngle());
}
