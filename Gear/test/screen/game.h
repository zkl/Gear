#ifndef GAME_H
#define GAME_H

#include "../../src/screen.h"
#include "../../src/world.h"
#include "../../src/tilemap/tilemap.h"

class Game : public Screen
{
public:
	virtual bool init();
	virtual void draw(SDL_Renderer* render);
	virtual void update(unsigned int dt);
	virtual void handleEvent(const SDL_Event& event);

private:
	World _world;
	TileMap _tilemap;
};

inline bool Game::init()
{
	_tilemap.load("test.tmx");
	_world.appendChild(&_tilemap);

	return true;
}

inline void Game::draw(SDL_Renderer* render)
{
	_world.draw(render);
}

inline void Game::update(unsigned int dt)
{
	_world.update(dt);
}

inline void Game::handleEvent(const SDL_Event& event)
{
	switch (event.type)
	{
		case SDL_MOUSEMOTION:
		{
			if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) 
			{
				_tilemap.move(event.motion.xrel, event.motion.yrel);
			}
			break;
		}
		case SDL_KEYDOWN:
		{
			const Uint8* sta = SDL_GetKeyboardState(0);
			if(sta[SDL_SCANCODE_Q])
				_tilemap.setVisiable(!_tilemap.visiable());
			break;
		}
	default:
		break;
	}
}

#endif