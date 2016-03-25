#include "../../src/sdlgame.h"
#include "screen/game.h"
#include "screen/menu.h"

int main(int argc, char * argv[])
{
	SDLGame * game = SDLGame::getSDLGame();

	Director::getDirector()->addScreen("menu", new Menu());
	Director::getDirector()->changeScreen("game");

	game->init("SDL2 Game Demo", 640, 480, 0);
	game->run();

	return 0;
}
