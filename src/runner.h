#ifndef RUNNER_H
#define RUNNER_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>

#include "sdlgame.h"
#include "world.h"
#include "tilemap/tilemap.h"
#include "sprite.h"
#include "spritesheet.h"
#include "image.h"

class Runner : public SDLGame
{
public:
	Runner();
	~Runner();

	virtual bool init(const char * title, int w, int h, int flags);
	virtual bool running();

	virtual void update();
	virtual void render();
	virtual void handleEvents();

private:
	unsigned int m_luptime;

	Image * _image;
	World * m_world;
	TileMap * _tilemap;
	SpriteSheet * _sprite;
	std::vector<Sprite * > m_sprites;

	SDL_Window * m_window;
	SDL_Renderer * m_renderer;
	bool m_isRunning;	
};

inline Runner::Runner() : 
	m_world(0),
	m_renderer(0),
	m_isRunning(false)
{
}

inline Runner::~Runner()
{
	if(m_window != 0)
		SDL_DestroyWindow(m_window);

	if(m_renderer != 0)
		SDL_DestroyRenderer(m_renderer);

	IMG_Quit();
	SDL_Quit();
}

inline bool Runner::running() 
{
	return m_isRunning;
}

#endif
