#pragma once
#include <Box2D/Box2D.h>
#include <glm/glm.hpp>
#include "Vertex.h"
#include "SpriteBatch.h"
#include "GLTexture.h"

class Box 
{
public:
	Box();
	~Box();

	void init(b2World* t_world, const glm::vec2& t_position, const glm::vec2& t_dimensions, GLTexture t_texture, ColorRGBA8 t_color, bool t_fixedRotation, bool t_isDynamic, float t_angle = 0.0f, glm::vec4 t_uvRect = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	void destroy(b2World* t_world);
	void draw(SpriteBatch& t_spriteBatch);

	bool isDynamic() const { return m_body->GetType() == b2_dynamicBody; }

	// Test if a point is inside the box
	bool testPoint(float t_x, float t_y) const { return m_fixture->TestPoint(b2Vec2(t_x, t_y)); }

	// Beautiful accessors
	b2Body*                    getBody()          const { return m_body; }
	b2Fixture*                 getFixture()       const { return m_fixture; }
	const glm::vec2&           getDimensions()    const { return m_dimensions; }
	glm::vec2                  getPosition()      const { return glm::vec2(m_body->GetPosition().x, m_body->GetPosition().y); }
	glm::vec4                  getUvRect()        const { return m_uvRect; }
	const ColorRGBA8&		   getColor()         const { return m_color; }
	float                      getAngle()         const { return m_body->GetAngle(); }
	const GLTexture&		   getTexture()       const { return m_texture; }
	const bool&                getFixedRotation() const { return m_fixedRotation; }
	const bool&                getIsDynamic()     const { return m_isDynamic; }
private:
	glm::vec4 m_uvRect;
	b2Body* m_body = nullptr;
	b2Fixture* m_fixture = nullptr;
	glm::vec2 m_dimensions;
	ColorRGBA8 m_color;
	GLTexture m_texture;
	bool m_fixedRotation;
	bool m_isDynamic;
};

