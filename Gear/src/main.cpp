#include "sdlgame.h"
#include "../test/screen/game.h"
#include "../test/screen/menu.h"

int main(int argc, char * argv[])
{
	SDLGame * game = SDLGame::getSDLGame();

	Director::getDirector()->addScreen("menu", new Menu());
	Director::getDirector()->addScreen("game", new Game());
	Director::getDirector()->changeScreen("game");

	game->init("SDL2 Game Demo", 640, 480, 0);
	game->run();

	return 0;
}
