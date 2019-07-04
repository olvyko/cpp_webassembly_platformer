#pragma once
#include <glm/glm.hpp>
#include <Box2D/Box2D.h>

#include "Vertex.h"
#include "SpriteBatch.h"
#include "InputManager.h"
#include "TileSheet.h"
#include "Capsule.h"

enum class PlayerMoveState { STANDING, RUNNING, PUNCHING, IN_AIR };

class Player 
{
public:
	void init(b2World* t_world, const glm::vec2& t_position, const glm::vec2& t_drawDims, const glm::vec2& t_collisionDims, ColorRGBA8 t_color);
	void destroy(b2World* t_world);
	void draw(SpriteBatch& t_spriteBatch);
	void update();

	const Capsule& getCapsule() const { return m_capsule; }
	glm::vec2 getPosition() const {
		glm::vec2 rv;
		rv.x = m_capsule.getBody()->GetPosition().x;
		rv.y = m_capsule.getBody()->GetPosition().y;
		return rv;
	}
	const glm::vec2& getDrawDims() const { return m_drawDims; }
	const glm::vec2& getCollisionDims() const { return m_collisionDims; }
	const ColorRGBA8& getColor() const { return m_color; }

private:
	glm::vec2 m_drawDims;
	glm::vec2 m_collisionDims;
	ColorRGBA8 m_color;
	TileSheet m_texture;
	Capsule m_capsule;
	PlayerMoveState m_moveState = PlayerMoveState::STANDING;
	float m_animTime = 0.0f;
	int m_direction = 1; // 1 or -1
	bool m_onGround = false;
	bool m_isPunching = false;
};
