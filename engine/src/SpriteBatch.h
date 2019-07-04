
#ifndef SPRITE_BATCH_H
#define SPRITE_BATCH_H

#include <vector>

#include "Glyph.h"
#include "RenderBatch.h"

/*
Texture batching: Sorting sprites by the texture used, and then simultaneously 
rendering as many sprites that use the same texture as possible, changing only 
the source area on the texture and the destination area on the render target 
between sprites. This allows the encapsulation of the whole operation in a single 
GPU command, reducing the overhead drastically from multiple distinct calls.
*/

// The SpriteBatch class is a more efficient way of drawing sprites
class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();

	// Initializes the spritebatch
	void init();
	void dispose();

	// Begins the spritebatch
	void begin(GlyphSortType t_sortType = GlyphSortType::TEXTURE);
	// Ends the spritebatch
	void end();

	// Adds a glyph to the spritebatch
	void addGlyph(const glm::vec4& t_destRect, const glm::vec4& t_uvRect, GLuint t_texture, float t_depth, const ColorRGBA8& t_color);
	// Adds a glyph to the spritebatch with rotation
	void addGlyph(const glm::vec4& t_destRect, const glm::vec4& t_uvRect, GLuint t_texture, float t_depth, const ColorRGBA8& t_color, float t_angle);
	// Adds a glyph to the spritebatch with rotation
	void addGlyph(const glm::vec4& t_destRect, const glm::vec4& t_uvRect, GLuint t_texture, float t_depth, const ColorRGBA8& t_color, const glm::vec2& t_dir);

	// Renders the entire SpriteBatch to the screen
	void renderBatch();
private:
	// Creates all the needed RenderBatches
	void createRenderBatches();

	// Generates our VAO and VBO
	void createVertexArray();

	// Sorts glyphs according to _sortType
	void sortGlyphs();

	// Comparators used by sortGlyphs()
	static bool compareFrontToBack(Glyph* t_a, Glyph* t_b);
	static bool compareBackToFront(Glyph* t_a, Glyph* t_b);
	static bool compareTexture(Glyph* t_a, Glyph* t_b);

	GLuint m_vbo;
	GLuint m_vao;

	GlyphSortType m_sortType;

	// This is for sorting
	std::vector<Glyph*> m_glyphPointers;
	// These are the actual glyphs
	std::vector<Glyph> m_glyphs;

	std::vector<RenderBatch> m_renderBatches;
};

#endif // SPRITE_BATCH_H
