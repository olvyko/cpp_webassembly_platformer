
#ifndef EXTENSION_MANAGER_H
#define EXTENSION_MANAGER_H

#ifndef __EMSCRIPTEN__

#include <SDL.h>

///Calculates FPS and also limits FPS
class FpsLimiter
{
public:
	FpsLimiter();

	// Initializes the FPS limiter. For now, this is
	// analogous to setMaxFPS
	void init(float t_maxFPS);

	// Sets the desired max FPS
	void setMaxFPS(float t_maxFPS);

	void begin();

	// end() will return the current FPS as a float
	float end();
private:
	// Calculates the current FPS
	void calculateFPS();

	// Variables
	float m_fps;
	float m_maxFPS;
	float m_frameTime;
	unsigned int m_startTicks;
};

#endif

#endif // EXTENSION_MANAGER_H
