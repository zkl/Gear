#include "src/sdlgame.h"
#include "gamescreen.h"

int main(int argc, char * argv[])
{
	SDLGame * game = SDLGame::getSDLGame();

	GameScreen* screen = new GameScreen();
	Director::getDirector()->addScreen("Tank", screen);

	game->init("SDL2 Game Demo - Tank", 640, 480, 0);
	game->run();

	return 0;
}
