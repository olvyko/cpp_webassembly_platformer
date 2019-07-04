
#ifndef RENDER_BATCH_H
#define RENDER_BATCH_H

#include <GL/glew.h>

// Each render batch is used for a single draw call
class RenderBatch
{
public:
	RenderBatch(GLuint t_offset, GLuint t_numVertices, GLuint t_texture) :
		offset(t_offset),
		numVertices(t_numVertices),
		texture(t_texture) {
	}
	GLuint offset;
	GLuint numVertices;
	GLuint texture;
};

#endif // RENDER_BATCH_H
