#include "ImageLoader.h"
#include "GameErrors.h"
#include "picoPNG.h"
#include "IOManager.h"

ImageLoader* ImageLoader::m_instance;

ImageLoader::ImageLoader()
{
}

ImageLoader::~ImageLoader()
{
}

ImageLoader* ImageLoader::getInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new ImageLoader();
		return m_instance;
	}

	// Point to same object (singleton pattern)
	return m_instance;
}

GLTexture ImageLoader::loadPNG(std::string t_filePath)
{
	// Create a GLTexture and initialize all its fields to 0
	GLTexture texture = {};

	//This is the input data to decodePNG, which we load from a file
	std::vector<unsigned char> in;
	//This is the output data from decodePNG, which is the pixel data for our texture
	std::vector<unsigned char> out;

	unsigned long width, height;

	//Read in the image file contents into a buffer
	if (IOManager::getInstance()->readFileToBuffer(t_filePath, in) == false)
	{
		fatalError("Failed to load PNG file to buffer!");
	}

	//Decode the .png format into an array of pixels
	int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
	if (errorCode != 0) 
	{
		fatalError("decodePNG failed with error: " + std::to_string(errorCode));
	}

	//Generate the openGL texture object
	glGenTextures(1, &(texture.id));

	//Bind the texture object
	glBindTexture(GL_TEXTURE_2D, texture.id);
	//Upload the pixels to the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

	//Set some texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//Generate the mipmaps
	glGenerateMipmap(GL_TEXTURE_2D);

	//Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	texture.width = width;
	texture.height = height;
	texture.filePath = t_filePath;

	//Return a copy of the texture data
	return texture;
}
