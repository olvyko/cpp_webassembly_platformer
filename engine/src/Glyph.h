
#ifndef GLYPH_H
#define GLYPH_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Vertex.h"

// Determines how we should sort the glyphs
enum class GlyphSortType 
{
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};

// A glyph is a single quad. These are added via SpriteBatch::addGlyph
class Glyph 
{
public:
	Glyph() {};
	Glyph(const glm::vec4& t_destRect, const glm::vec4& t_uvRect, GLuint t_texture, float t_depth, const ColorRGBA8& t_color);
	Glyph(const glm::vec4& t_destRect, const glm::vec4& t_uvRect, GLuint t_texture, float t_depth, const ColorRGBA8& t_color, float t_angle);

	GLuint texture;
	float depth;

	Vertex topLeft;
	Vertex bottomLeft;
	Vertex topRight;
	Vertex bottomRight;
private:
	// Rotates a point about (0,0) by angle
	glm::vec2 rotatePoint(const glm::vec2& pos, float angle);
};

#endif // GLYPH_H
