#include "TileSheet.h"

void TileSheet::init(const GLTexture& t_texture, const glm::ivec2& t_tileDims)
{
	texture = t_texture;
	dims = t_tileDims;
}

glm::vec4 TileSheet::getUVs(int t_index)
{
	int xTile = t_index % dims.x;
	int yTile = t_index / dims.x;

	glm::vec4 uvs;
	uvs.x = xTile / (float)dims.x;
	uvs.y = yTile / (float)dims.y;
	uvs.z = 1.0f / dims.x;
	uvs.w = 1.0f / dims.y;

	return uvs;
}
