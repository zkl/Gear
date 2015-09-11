#ifndef GAME_H
#define GAME_H

#include "../../src/screen.h"
#include "../../src/world.h"
#include "../../src/tilemap/tilemap.h"
#include "../../src/movie.h"
#include "../../src/spritesheet.h"

class Game : public Screen
{
public:
	virtual bool init();
	virtual void draw(SDL_Renderer* render);
	virtual void update(unsigned int dt);
	virtual void handleEvent(const SDL_Event& event);

private:
	Image _image;
	Movie _movie;
	World _world;
	TileMap _tilemap;
};

inline bool Game::init()
{
	_tilemap.load("game.tmx");
	
	_world.appendChild(&_tilemap);
	_world.appendChild(&_movie);
	_world.setActive();

	_image.load("b.png");
	//_image.resize(187, 64);
	_image.resize(200, 100);
	//Image image("om.png");
	_movie.addFrame(&_image);
	//_movie.addFrames(&image, 0, 0, 163, 133, 2, 6);
	_movie.loop();
	_movie.play();
	_movie.setActive();
	_movie.setPosition(100, 200);

	return true;
}

inline void Game::draw(SDL_Renderer* render)
{
	_world.draw(render);
}

inline void Game::update(unsigned int dt)
{
	_movie.setPosition(_movie.x()+10, _movie.y());
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
				//_tilemap.move(event.motion.xrel, event.motion.yrel);
			}
			break;
		}
		case SDL_KEYDOWN:
		{
			const Uint8* sta = SDL_GetKeyboardState(0);
			if(sta[SDL_SCANCODE_Q])
				_tilemap.setVisiable(!_tilemap.visiable());

			_movie.setPosition(0, 239);
			break;
		}
	default:
		break;
	}
}

#endif
