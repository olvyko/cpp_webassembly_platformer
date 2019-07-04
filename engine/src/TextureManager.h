
#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <string>
#include <map>

#include "GLTexture.h"

class TextureManager
{
public:
	static TextureManager* getInstance();
	GLTexture load(const std::string& t_filename);
private:
	TextureManager();
	~TextureManager();

	TextureManager(TextureManager const&) = delete;
	TextureManager& operator=(TextureManager const&) = delete;

	std::map<std::string, GLTexture> m_loadedTextures;
	static TextureManager* m_instance;
};

#endif // TEXTURE_MANAGER_H
