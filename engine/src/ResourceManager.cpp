#include "ResourceManager.h"

ResourceManager* ResourceManager::m_instance;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

ResourceManager* ResourceManager::getInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new ResourceManager();
		return m_instance;
	}

	// Point to same object (singleton pattern)
	return m_instance;
}

GLTexture ResourceManager::getTexture(const std::string& t_texturePath)
{
	return TextureManager::getInstance()->load(t_texturePath);
}
