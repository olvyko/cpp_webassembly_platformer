#include "Glyph.h"

Glyph::Glyph(const glm::vec4& t_destRect, const glm::vec4& t_uvRect, GLuint t_texture, float t_depth, const ColorRGBA8& t_color) :
	texture(t_texture),
	depth(t_depth)
{
	topLeft.color = t_color;
	topLeft.setPosition(t_destRect.x, t_destRect.y + t_destRect.w);
	topLeft.setUV(t_uvRect.x, t_uvRect.y + t_uvRect.w);

	bottomLeft.color = t_color;
	bottomLeft.setPosition(t_destRect.x, t_destRect.y);
	bottomLeft.setUV(t_uvRect.x, t_uvRect.y);

	bottomRight.color = t_color;
	bottomRight.setPosition(t_destRect.x + t_destRect.z, t_destRect.y);
	bottomRight.setUV(t_uvRect.x + t_uvRect.z, t_uvRect.y);

	topRight.color = t_color;
	topRight.setPosition(t_destRect.x + t_destRect.z, t_destRect.y + t_destRect.w);
	topRight.setUV(t_uvRect.x + t_uvRect.z, t_uvRect.y + t_uvRect.w);
}

Glyph::Glyph(const glm::vec4& t_destRect, const glm::vec4& t_uvRect, GLuint t_texture, float t_depth, const ColorRGBA8& t_color, float t_angle) :
	texture(t_texture),
	depth(t_depth)
{
	glm::vec2 halfDims(t_destRect.z / 2.0f, t_destRect.w / 2.0f);

	// Get points centered at origin
	glm::vec2 tl(-halfDims.x, halfDims.y);
	glm::vec2 bl(-halfDims.x, -halfDims.y);
	glm::vec2 br(halfDims.x, -halfDims.y);
	glm::vec2 tr(halfDims.x, halfDims.y);

	// Rotate the points
	tl = rotatePoint(tl, t_angle) + halfDims;
	bl = rotatePoint(bl, t_angle) + halfDims;
	br = rotatePoint(br, t_angle) + halfDims;
	tr = rotatePoint(tr, t_angle) + halfDims;

	topLeft.color = t_color;
	topLeft.setPosition(t_destRect.x + tl.x, t_destRect.y + tl.y);
	topLeft.setUV(t_uvRect.x, t_uvRect.y + t_uvRect.w);

	bottomLeft.color = t_color;
	bottomLeft.setPosition(t_destRect.x + bl.x, t_destRect.y + bl.y);
	bottomLeft.setUV(t_uvRect.x, t_uvRect.y);

	bottomRight.color = t_color;
	bottomRight.setPosition(t_destRect.x + br.x, t_destRect.y + br.y);
	bottomRight.setUV(t_uvRect.x + t_uvRect.z, t_uvRect.y);

	topRight.color = t_color;
	topRight.setPosition(t_destRect.x + tr.x, t_destRect.y + tr.y);
	topRight.setUV(t_uvRect.x + t_uvRect.z, t_uvRect.y + t_uvRect.w);
}

glm::vec2 Glyph::rotatePoint(const glm::vec2& pos, float angle)
{
	glm::vec2 newv;
	newv.x = pos.x * cos(angle) - pos.y * sin(angle);
	newv.y = pos.x * sin(angle) + pos.y * cos(angle);
	return newv;
}
