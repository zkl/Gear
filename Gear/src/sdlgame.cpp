#include <SDL2/SDL.h>
#include "sdlgame.h"
#include "screen.h"

void SDLGame::run()
{
	if(_inited)
	{
		while(this->running())
		{
			this->handleEvents();
			this->update();
			this->render();
		};
	}
}

void SDLGame::update()
{
	unsigned int time = SDL_GetTicks();

	Screen* screen = _director->currentScreen();
	if(screen != 0)
		screen->update(time - _uptime);

	_uptime = time;
}

void SDLGame::handleEvents()
{
	SDL_Event event;
	if(SDL_WaitEventTimeout(&event, 1) == 0)
		return ;

	if(event.type ==  SDL_QUIT)
		this->stop();

	Screen* screen = _director->currentScreen();
	if(screen != 0)
		screen->handleEvent(event);
}

void SDLGame::render()
{
	Screen* screen = _director->currentScreen();
	if(screen != 0)
	{
		SDL_RenderClear(_renderer);

		screen->draw(_renderer);

		SDL_RenderPresent(_renderer);
	}
}
