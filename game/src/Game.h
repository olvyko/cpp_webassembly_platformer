#pragma once

#ifdef __EMSCRIPTEN__
#include <SDL2/SDL.h>
#include <emscripten.h>
#else
#include <SDL.h>

#include "FpsLimiter.h"
#endif

#include "Player.h"
#include "Box.h"
#include "Camera2D.h"
#include "GLSLProgram.h"

class Game
{
public:
	Game();
	Game(int t_width, int t_height);
	~Game();

#ifdef __EMSCRIPTEN__
	void run(em_callback_func t_mainloopWrapper);
#else
	void run();
#endif

	void mainloop();
private:
	void init();
	void initEntities();
	void initShaders();
	void update();
	void input();
	void draw();
	void destroy();

	int m_width;
	int m_height;

	SDL_Window* m_window;
	SDL_Event m_event;

	GLSLProgram m_lightProgram;
	GLSLProgram m_textureProgram;
	Camera2D m_camera;
	SpriteBatch m_spriteBatch;
	GLTexture m_texture;

	Player m_player;
	std::vector<Box> m_boxes;
	std::unique_ptr<b2World> m_world;

	bool m_isRunning = false;

#ifndef __EMSCRIPTEN__
	FpsLimiter m_limiter;
#endif
};
