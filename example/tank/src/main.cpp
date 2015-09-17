#include "src/sdlgame.h"
#include "gamescreen.h"
#include "startscreen.h"
#include "gameoverscreen.h"

int main(int argc, char * argv[])
{
	SDLGame * game = SDLGame::getSDLGame();

	Director::getDirector()->addScreen("Menu", new StartScreen());
	Director::getDirector()->addScreen("Game", new GameScreen());
	Director::getDirector()->addScreen("GameOver", new GameOverScreen());

	Director::getDirector()->changeScreen("Menu");

	game->init("SDL2 Game Demo - Tank", 640, 480, 0);
	game->run();

	return 0;
}
