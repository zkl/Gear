#include <SDL2/SDL.h>
#include "sdlgame.h"
#include "screen.h"

SDLGame::SDLGame() : 
	_interval(1000/60),
	_inited(false)
{
	_director = Director::getDirector();
}

SDLGame::~SDLGame()
{
	if(_window != 0)
		SDL_DestroyWindow(_window);

	if(_renderer != 0)
		SDL_DestroyRenderer(_renderer);

	_window = 0;
	_renderer = 0;
	_inited = false;

	IMG_Quit();
	SDL_Quit();
}

bool SDLGame::init(const char * title, int w, int h, int flags)
{
	_isRunning = true;
	_uptime = 0;
	
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return false;

	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

	_window = SDL_CreateWindow(title, 100, 100, w, h, flags);

	if(_window == 0)
		return false;

	_renderer = SDL_CreateRenderer(_window, -1, 0);
	if(_renderer == 0)
		return false;

	_inited = true;
	return true;
}

void SDLGame::run()
{
	if(_inited)
	{
		while(this->running())
		{
			unsigned int time = SDL_GetTicks();
			this->handleEvents();
			this->update(time-_uptime);
			this->render();
			_uptime = time;
		};
	}
}

void SDLGame::update(int dt)
{
	Screen* screen = _director->currentScreen();
	if(screen != 0)
		screen->update(dt);
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
