#include "Game.h"

int main(int argc, char* argv[])
{
#ifdef __EMSCRIPTEN__
	static Game game(500, 500);
	game.run([]() { game.mainloop(); });
#else
	Game game(500, 500);
	game.run();
#endif
	return 0;
}