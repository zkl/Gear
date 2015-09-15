#include "src/route/astar/astar.h"
#include "gamescreen.h"
#include <stdlib.h>
#include <time.h>

bool GameScreen::init()
{
	_tilemap.load("map.tmx");

	_world.appendChild(&_tilemap);
	_world.appendChild(&_tank);
	_world.init();

	_tank.setPosition(160, 160);
	_tank.setTileMap(&_tilemap);

	srand((unsigned int)time(0));
	return true;
}

void GameScreen::update(unsigned int dt)
{
	_world.update(dt);

	if(!_tank.moving())
	{
		const Uint8* sta = SDL_GetKeyboardState(0);
		if(sta[::SDL_SCANCODE_UP])
			_tank.turnUp();
		else if(sta[::SDL_SCANCODE_DOWN])
			_tank.turnDown();
		else if(sta[::SDL_SCANCODE_LEFT])
			_tank.turnLeft();
		else if(sta[::SDL_SCANCODE_RIGHT])
			_tank.turnRight();
	}
}

void GameScreen::draw(SDL_Renderer* renderer)
{
	_world.draw(renderer);
}

void GameScreen::handleEvent(const SDL_Event& event)
{
	switch (event.type)
	{	
		case SDL_MOUSEBUTTONDOWN:
		{
			break;
		}
		case SDL_MOUSEMOTION:
		{
			break;
		}
		case SDL_KEYDOWN:
		{
			const Uint8* sta = SDL_GetKeyboardState(0);
			if(sta[::SDL_SCANCODE_SPACE])
			{
				_tank.fire();
			}
			break;
		}
	default:
		break;
	}
}

