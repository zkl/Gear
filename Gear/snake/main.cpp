#include "../src/sdlgame.h"
#include "snakegame.h"

int main(int argc, char * argv[])
{
	SDLGame * game = SDLGame::getSDLGame();

	SnakeGame* snake = new SnakeGame();
	Director::getDirector()->addScreen("game", snake);

	game->init("SDL2 Game Demo - Snake ", 640, 480, 0);
	game->run();

	return 0;
}
