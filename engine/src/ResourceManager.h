
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <string>

#include "TextureManager.h"

class ResourceManager
{
public:
	static ResourceManager* getInstance();
	GLTexture getTexture(const std::string& t_texturePath);

private:
	ResourceManager();
	~ResourceManager();

	ResourceManager(ResourceManager const&) = delete;
	ResourceManager& operator=(ResourceManager const&) = delete;

	static ResourceManager* m_instance;
};

#endif // RESOURCE_MANAGER_H
