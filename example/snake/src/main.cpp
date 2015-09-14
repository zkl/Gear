#include "src/sdlgame.h"
#include "gamescreen.h"

int main(int argc, char * argv[])
{
	SDLGame * game = SDLGame::getSDLGame();

	GameScreen* snake = new GameScreen();
	Director::getDirector()->addScreen("game", snake);

	game->init("SDL2 Game Demo - Snake ", 640, 480, 0);
	game->run();

	return 0;
}
