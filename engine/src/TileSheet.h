
#ifndef TILE_SHEET_H
#define TILE_SHEET_H

#include <glm/glm.hpp>
#include "GLTexture.h"

class TileSheet 
{
public:
	void init(const GLTexture& t_texture, const glm::ivec2& t_tileDims);
	glm::vec4 getUVs(int t_index);

	GLTexture texture;
	glm::ivec2 dims;
};

#endif // TILE_SHEET_H
