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
	void setFps(int fps);

	virtual bool init(const char * title, int w, int h, int flags);

protected:
	SDLGame();
	virtual ~SDLGame();

	bool running();
	virtual void handleEvents();
	virtual void render();
	virtual void update(int dt);

private:
	bool _inited;
	bool _isRunning;
	unsigned int  _interval;
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

inline void SDLGame::stop()
{
	_isRunning = false;
}


inline void SDLGame::setFps(int fps)
{
	_interval = 1000/fps;
}

inline bool SDLGame::running()
{
	return _isRunning;
}


#endif
