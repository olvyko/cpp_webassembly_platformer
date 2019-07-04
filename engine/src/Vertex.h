
#ifndef VERTEX_H
#define VERTEX_H

#include <GL/glew.h>

struct Position 
{
	float x;
	float y;
};

struct ColorRGBA8 
{
	ColorRGBA8() : r(0), g(0), b(0), a(0) { }
	ColorRGBA8(GLubyte t_r, GLubyte t_g, GLubyte t_b, GLubyte t_a) :
		r(t_r), g(t_g), b(t_g), a(t_a) { }
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

struct ColorFloat 
{
	ColorFloat() : r(0.0f), g(0.0f), b(0.0f), a(0.0f) { }
	ColorFloat(GLclampf t_r, GLclampf t_g, GLclampf t_b, GLclampf t_a) :
		r(t_r), g(t_g), b(t_g), a(t_a) { }

	GLclampf r;
	GLclampf g;
	GLclampf b;
	GLclampf a;
};

struct UV 
{
	float u;
	float v;
};

// The vertex definition
struct Vertex 
{
	// This is the position struct. When you store a struct or class
	// inside of another struct or class, it is called composition. This is
	// layed out exactly the same in memory as if we had a float position[2],
	// but doing it this way makes more sense.
	Position position;

	// 4 bytes for r g b a color.
	ColorRGBA8 color;

	// UV texture coordinates.
	UV uv;

	void setPosition(float t_x, float t_y)
	{
		position.x = t_x;
		position.y = t_y;
	}

	void setColor(GLubyte t_r, GLubyte t_g, GLubyte t_b, GLubyte t_a)
	{
		color.r = t_r;
		color.g = t_g;
		color.b = t_b;
		color.a = t_a;
	}

	void setUV(float t_u, float t_v)
	{
		uv.u = t_u;
		uv.v = t_v;
	}
};

#endif // VERTEX_H
