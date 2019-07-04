#include "Game.h"
#include "GLTexture.h"
#include "ResourceManager.h"
#include "GameErrors.h"
#include "ExtensionManager.h"
#include "InputManager.h"

#include <iostream>
#include <string>
#include <random>

Game::Game() : 
	m_width(320),
	m_height(320)
{
}

Game::Game(int t_width, int t_height) : 
	m_width(t_width),
	m_height(t_height)
{
}

Game::~Game()
{
}

#ifdef __EMSCRIPTEN__
void Game::run(em_callback_func t_mainloopWrapper)
{
	init();
	initEntities();

	m_isRunning = true;
	emscripten_set_main_loop(t_mainloopWrapper, -1, 1);
	destroy();
}

#else
void Game::run()
{
	init();
	initEntities();

	m_limiter.setMaxFPS(60.0f);

	m_isRunning = true;
	while (m_isRunning)
	{
		mainloop();
	}
	destroy();
}
#endif

void Game::init()
{
	// Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	// Tell SDL that we want a double buffered window
	// so we dont get any flickering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	// Open an SDL window
	m_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_OPENGL);
	if (m_window == nullptr) 
	{
		fatalError("SDL Window could not be created!");
	}

	// Set up our OpenGL context
	SDL_GLContext glContext = SDL_GL_CreateContext(m_window);
	if (glContext == nullptr) 
	{
		fatalError("SDL_GL context could not be created!");
	}

	// Set up glew (optional but recommended)
	GLenum error = glewInit();
	if (error != GLEW_OK) 
	{
		fatalError("Could not initialize glew!");
	}

	// Set the background color to blue
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	// Set VSYNC
	SDL_GL_SetSwapInterval(0);

	// Enable alpha blend
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Game::initEntities()
{
	b2Vec2 gravity(0.0f, -25.0f);
	m_world = std::unique_ptr<b2World>(new b2World(gravity));

	// Load the texture
	m_texture = ResourceManager::getInstance()->getTexture("assets/images/bricks_top.png");

    // Make the ground
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -20.0f);
    b2Body* groundBody = m_world->CreateBody(&groundBodyDef);
    // Make the ground fixture
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);

	// Make a bunch of boxes
	std::mt19937 randGenerator;
	std::uniform_real_distribution<float> xPos(-10.0, 10.0f);
	std::uniform_real_distribution<float> yPos(-10.0, 25.0f);
	std::uniform_real_distribution<float> size(0.5, 2.5f);
	std::uniform_int_distribution<int> color(50, 255);
	const int NUM_BOXES = 100;

	for (int i = 0; i < NUM_BOXES; i++) 
	{
		ColorRGBA8 randColor;
		randColor.r = color(randGenerator);
		randColor.g = color(randGenerator);
		randColor.b = color(randGenerator);
		randColor.a = 255;
		Box newBox;
		newBox.init(m_world.get(), glm::vec2(xPos(randGenerator), yPos(randGenerator)), glm::vec2(size(randGenerator), size(randGenerator)), m_texture, randColor, false, true);
		m_boxes.push_back(newBox);
	}

	// Initialize spritebatch
	m_spriteBatch.init();

	// Shader init
	initShaders();

	// Init camera
	m_camera.init(m_width, m_height);
	m_camera.setScale(15.0f);

	// Init player
	m_player.init(m_world.get(), glm::vec2(0.0f, 30.0f), glm::vec2(2.0f), glm::vec2(1.0f, 1.8f), ColorRGBA8(255, 255, 255, 255));
}

void Game::initShaders()
{
	// Compile our texture
	m_textureProgram.compileShaders("shaders/textureShading.vert", "shaders/textureShading.frag");
	m_textureProgram.addAttribute("vertexPosition");
	m_textureProgram.addAttribute("vertexColor");
	m_textureProgram.addAttribute("vertexUV");
	m_textureProgram.linkShaders();
	// Compile our light shader
	m_lightProgram.compileShaders("shaders/lightShading.vert", "shaders/lightShading.frag");
	m_lightProgram.addAttribute("vertexPosition");
	m_lightProgram.addAttribute("vertexColor");
	m_lightProgram.addAttribute("vertexUV");
	m_lightProgram.linkShaders();
}

void Game::mainloop()
{
#ifndef __EMSCRIPTEN__
	m_limiter.begin();
#endif

	input();

	if (m_isRunning)
	{
		update();
		draw();

#ifndef __EMSCRIPTEN__
		float fps = m_limiter.end();
#endif
		SDL_GL_SwapWindow(m_window);
	}
}

void Game::update()
{
	m_camera.update();
	m_player.update();

	// Update the physics simulation
	m_world->Step(1.0f / 60.0f, 6, 2);
}

void Game::input()
{
	// Update input manager
	auto inputManager = InputManager::getInstance();
	inputManager->update();

	while (SDL_PollEvent(&m_event))
	{
		switch (m_event.type)
		{
		case SDL_QUIT:
			m_isRunning = false;
			break;
		case SDL_MOUSEMOTION:
			inputManager->setMouseCoords(glm::vec2((float)m_event.motion.x, (float)m_event.motion.y));
			break;
		case SDL_KEYDOWN:
			inputManager->pressKey(m_event.key.keysym.sym);
			break;
		case SDL_KEYUP:
			inputManager->releaseKey(m_event.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			inputManager->pressKey(m_event.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			inputManager->releaseKey(m_event.button.button);
			break;
		}
	}
}

void Game::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	m_textureProgram.use();

	// Upload texture uniform
	GLint textureUniform = m_textureProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	glActiveTexture(GL_TEXTURE0);

	// Camera matrix
	glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
	GLint pUniform = m_textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	m_spriteBatch.begin();

	// Draw all the boxes
	for (auto& b : m_boxes) 
	{
		b.draw(m_spriteBatch);
	}
	m_player.draw(m_spriteBatch);

	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_textureProgram.unuse();

	// Reset to regular alpha blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Game::destroy()
{
	m_boxes.clear();
	m_world.reset();

	SDL_DestroyWindow(m_window);
	SDL_Quit();
}
