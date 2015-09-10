#ifndef SDL_GAME_H
#define SDL_GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "director.h"

class SDLGame
{
public:
	static SDLGame* getSDLGame();
	void run();
	void stop();
	virtual bool init(const char * title, int w, int h, int flags);

protected:
	SDLGame();
	virtual ~SDLGame();

	bool running();
	virtual void handleEvents();
	virtual void render();
	virtual void update();

private:
	bool _inited;
	bool _isRunning;
	unsigned int _uptime;
	Director* _director;
	SDL_Window * _window;
	SDL_Renderer * _renderer;
};

inline SDLGame* SDLGame::getSDLGame()
{
	static SDLGame sdlgame;
	return &sdlgame;
}

inline SDLGame::SDLGame()
{
	_inited = false;
	_director = Director::getDirector();
}

inline SDLGame::~SDLGame()
{
	if(_window != 0)
		SDL_DestroyWindow(_window);

	if(_renderer != 0)
		SDL_DestroyRenderer(_renderer);

	_window = 0;
	_renderer = 0;
	IMG_Quit();
	SDL_Quit();
}

inline void SDLGame::stop()
{
	_isRunning = false;
}

inline bool SDLGame::init(const char * title, int w, int h, int flags)
{
	_isRunning = true;
	_uptime = 0;
	
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return false;

	IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG);

	_window = SDL_CreateWindow(title, 100, 100, w, h, flags);

	if(_window == 0)
		return false;

	_renderer = SDL_CreateRenderer(_window, -1, 0);
	if(_renderer == 0)
		return false;

	_inited = true;
	return true;
}

inline bool SDLGame::running()
{
		return _isRunning;
}


#endif
