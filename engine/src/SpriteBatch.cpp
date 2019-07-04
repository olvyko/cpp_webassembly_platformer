#include "SpriteBatch.h"
#include <algorithm>

SpriteBatch::SpriteBatch() :
	m_vbo(0), m_vao(0)
{
}

SpriteBatch::~SpriteBatch()
{
}

void SpriteBatch::init()
{
	createVertexArray();
}

void SpriteBatch::dispose()
{
	if (m_vao != 0) 
	{
		glDeleteVertexArrays(1, &m_vao);
		m_vao = 0;
	}

	if (m_vbo != 0) 
	{
		glDeleteBuffers(1, &m_vbo);
		m_vbo = 0;
	}
}

void SpriteBatch::begin(GlyphSortType t_sortType /*= GlyphSortType::TEXTURE*/)
{
	m_sortType = t_sortType;
	m_renderBatches.clear();

	// Makes _glpyhs.size() == 0, however it does not free internal memory.
	// So when we later call emplace_back it doesn't need to internally call new.
	m_glyphs.clear();
}

void SpriteBatch::end()
{
	// Set up all pointers for fast sorting
	m_glyphPointers.resize(m_glyphs.size());
	for (size_t i = 0; i < m_glyphs.size(); i++) 
	{
		m_glyphPointers[i] = &m_glyphs[i];
	}

	sortGlyphs();
	createRenderBatches();
}

void SpriteBatch::addGlyph(const glm::vec4& t_destRect, const glm::vec4& t_uvRect, GLuint t_texture, float t_depth, const ColorRGBA8& t_color)
{
	m_glyphs.emplace_back(t_destRect, t_uvRect, t_texture, t_depth, t_color);
}

void SpriteBatch::addGlyph(const glm::vec4& t_destRect, const glm::vec4& t_uvRect, GLuint t_texture, float t_depth, const ColorRGBA8& t_color, float t_angle)
{
	m_glyphs.emplace_back(t_destRect, t_uvRect, t_texture, t_depth, t_color, t_angle);
}

void SpriteBatch::addGlyph(const glm::vec4& t_destRect, const glm::vec4& t_uvRect, GLuint t_texture, float t_depth, const ColorRGBA8& t_color, const glm::vec2& t_dir)
{
	const glm::vec2 right(1.0f, 0.0f);
	float angle = acos(glm::dot(right, t_dir));
	if (t_dir.y < 0.0f)
	{
		angle = -angle;
	}

	m_glyphs.emplace_back(t_destRect, t_uvRect, t_texture, t_depth, t_color, angle);
}

void SpriteBatch::renderBatch()
{
	// Bind our VAO. This sets up the opengl state we need, including the 
	// vertex attribute pointers and it binds the VBO
	glBindVertexArray(m_vao);

	for (size_t i = 0; i < m_renderBatches.size(); i++) 
	{
		glBindTexture(GL_TEXTURE_2D, m_renderBatches[i].texture);
		glDrawArrays(GL_TRIANGLES, m_renderBatches[i].offset, m_renderBatches[i].numVertices);
	}

	glBindVertexArray(0);
}

void SpriteBatch::createRenderBatches()
{
	// This will store all the vertices that we need to upload
	std::vector <Vertex> vertices;
	// Resize the buffer to the exact size we need so we can treat
	// it like an array
	vertices.resize(m_glyphPointers.size() * 6);

	if (m_glyphPointers.empty()) 
	{
		return;
	}

	// current offset
	int offset = 0;
	// current vertex
	int cv = 0;

	//Add the first batch
	m_renderBatches.emplace_back(offset, 6, m_glyphPointers[0]->texture);
	vertices[cv++] = m_glyphPointers[0]->topLeft;
	vertices[cv++] = m_glyphPointers[0]->bottomLeft;
	vertices[cv++] = m_glyphPointers[0]->bottomRight;
	vertices[cv++] = m_glyphPointers[0]->bottomRight;
	vertices[cv++] = m_glyphPointers[0]->topRight;
	vertices[cv++] = m_glyphPointers[0]->topLeft;
	offset += 6;

	//Add all the rest of the glyphs
	for (size_t cg = 1; cg < m_glyphPointers.size(); cg++) 
	{
		// Check if this glyph can be part of the current batch
		if (m_glyphPointers[cg]->texture != m_glyphPointers[cg - 1]->texture) 
		{
			// Make a new batch
			m_renderBatches.emplace_back(offset, 6, m_glyphPointers[cg]->texture);
		}
		else 
		{
			// If its part of the current batch, just increase numVertices
			m_renderBatches.back().numVertices += 6;
		}
		vertices[cv++] = m_glyphPointers[cg]->topLeft;
		vertices[cv++] = m_glyphPointers[cg]->bottomLeft;
		vertices[cv++] = m_glyphPointers[cg]->bottomRight;
		vertices[cv++] = m_glyphPointers[cg]->bottomRight;
		vertices[cv++] = m_glyphPointers[cg]->topRight;
		vertices[cv++] = m_glyphPointers[cg]->topLeft;
		offset += 6;
	}

	// Bind our VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	// Orphan the buffer (for speed)
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	// Upload the data
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

	// Unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteBatch::createVertexArray()
{
	// Generate the VAO if it isn't already generated
	if (m_vao == 0) 
	{
		glGenVertexArrays(1, &m_vao);
	}

	// Bind the VAO. All subsequent opengl calls will modify it's state.
	glBindVertexArray(m_vao);

	// Generate the VBO if it isn't already generated
	if (m_vbo == 0) 
	{
		glGenBuffers(1, &m_vbo);
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	// Tell opengl what attribute arrays we need
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//This is the position attribute pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	//This is the color attribute pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	//This is the UV attribute pointer
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glBindVertexArray(0);
}

void SpriteBatch::sortGlyphs()
{
	switch (m_sortType) 
	{
	case GlyphSortType::BACK_TO_FRONT:
		std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareBackToFront);
		break;
	case GlyphSortType::FRONT_TO_BACK:
		std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareFrontToBack);
		break;
	case GlyphSortType::TEXTURE:
		std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareTexture);
		break;
	case GlyphSortType::NONE:
		break;
	}
}

bool SpriteBatch::compareFrontToBack(Glyph* t_a, Glyph* t_b)
{
	return (t_a->depth < t_b->depth);
}

bool SpriteBatch::compareBackToFront(Glyph* t_a, Glyph* t_b)
{
	return (t_a->depth > t_b->depth);
}

bool SpriteBatch::compareTexture(Glyph* t_a, Glyph* t_b)
{
	return (t_a->texture < t_b->texture);
}
