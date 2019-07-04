
#ifndef GL_TEXTURE_H
#define GL_TEXTURE_H

#include <GL/glew.h>
#include <string>

struct GLTexture
{
	std::string filePath = "";
	GLuint id;
	int width;
	int height;
};

#endif // GL_TEXTURE_H
