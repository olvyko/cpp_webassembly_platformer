#include "TextureManager.h"
#include "ImageLoader.h"

TextureManager* TextureManager::m_instance;

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

TextureManager* TextureManager::getInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new TextureManager();
		return m_instance;
	}

	// Point to same object (singleton pattern)
	return m_instance;
}

GLTexture TextureManager::load(const std::string& t_filename)
{
	// lookup the texture and see if its in the map
	auto mit = m_loadedTextures.find(t_filename);
	if (mit != m_loadedTextures.end())
	{
		return mit->second;
	}

	// Load the texture
	GLTexture newTexture = ImageLoader::getInstance()->loadPNG(t_filename);

	// Insert it into the map
	m_loadedTextures.insert(make_pair(t_filename, newTexture));

	return newTexture;
}
