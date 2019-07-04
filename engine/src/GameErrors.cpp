#include "GameErrors.h"

#include <cstdlib>

#include <iostream>

#ifdef __EMSCRIPTEN__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

//Prints out an error message and exits the game
void fatalError(std::string t_errorString) 
{
	std::cout << t_errorString << std::endl;
	SDL_Quit();
	exit(69);
}