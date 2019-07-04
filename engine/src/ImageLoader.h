
#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include <string>

#include "GLTexture.h"

// Loads images into GLTextures
class ImageLoader
{
public:
	static ImageLoader* getInstance();
	GLTexture loadPNG(std::string t_filePath);

private:
	ImageLoader();
	~ImageLoader();

	ImageLoader(ImageLoader const&) = delete;
	ImageLoader& operator=(ImageLoader const&) = delete;

	static ImageLoader* m_instance;
};

#endif // IMAGE_LOADER_H
