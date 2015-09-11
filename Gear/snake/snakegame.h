#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "../src/screen.h"
#include "../src/world.h"
#include "../src/tilemap/tilemap.h"
#include "snake.h"

class SnakeGame : public Screen
{
public:
	virtual bool init();
	virtual void draw(SDL_Renderer* render);
	virtual void update(unsigned int dt);
	virtual void handleEvent(const SDL_Event& event);

private:
	Snake _snake;
	World _world;
	TileMap _tilemap;
};

inline bool SnakeGame::init()
{
	_tilemap.load("game.tmx");
	_world.appendChild(&_tilemap);
	_world.appendChild(&_snake);
	_world.init();

	_snake.uplevel();
	_snake.uplevel();
	_snake.uplevel();
	_snake.uplevel();

	return true;
}

inline void SnakeGame::draw(SDL_Renderer* render)
{
	_world.draw(render);
}

inline void SnakeGame::update(unsigned int dt)
{
	_world.update(dt);
	if(_snake.dead() || 
		_tilemap.getGid(_snake.x(), _snake.y()) != 0 || 
		_tilemap.getGid(_snake.x()+_tilemap.tilsetWidth()-1, _snake.y()+_tilemap.tilsetHeight()-1))
	{
		_snake.setActive(false);
	}
}

inline void SnakeGame::handleEvent(const SDL_Event& event)
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
			if(sta[SDL_SCANCODE_W])
				_snake.turnUp();
			if(sta[SDL_SCANCODE_S])
				_snake.turnDown();
			if(sta[SDL_SCANCODE_A])
				_snake.turnLeft();
			if(sta[SDL_SCANCODE_D])
				_snake.turnRight();

			break;
		}
	default:
		break;
	}
}

#endif
