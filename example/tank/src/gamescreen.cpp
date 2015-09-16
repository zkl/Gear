#include "src/route/astar/astar.h"
#include "gamescreen.h"
#include <stdlib.h>
#include <time.h>

bool GameScreen::init()
{
	srand((unsigned int)time(0));

	_tilemap.load("map.tmx");

	_world.appendChild(&_tilemap);
	_world.appendChild(&_tank);

	for(unsigned int i=0; i<5; i++)
	{
		Robot* robot = new Robot();
		_robots.push_back(robot);
		_world.appendChild(_robots[i]);
	}

	_world.init();

	_tank.setPosition(160, 160);
	_tank.setTileMap(&_tilemap);

	for(unsigned int i=0; i<_robots.size(); i++)
		_robots[i]->setMap(&_tilemap);

	return true;
}

void GameScreen::update(unsigned int dt)
{
	_world.update(dt);

	if(!_tank.moving())
	{
		const Uint8* sta = SDL_GetKeyboardState(0);
		if(sta[::SDL_SCANCODE_W])
			_tank.turnUp();
		else if(sta[::SDL_SCANCODE_S])
			_tank.turnDown();
		else if(sta[::SDL_SCANCODE_A])
			_tank.turnLeft();
		else if(sta[::SDL_SCANCODE_D])
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
				_tank.fire();

			if(sta[::SDL_SCANCODE_P])
			{
				for(unsigned int i=0; i<_robots.size(); i++)
				{
					_robots[i]->setActive(false);
				}
			}
			else if(sta[::SDL_SCANCODE_G])
			{
				for(unsigned int i=0; i<_robots.size(); i++)
				{
					_robots[i]->setActive(true);
				}
			}

			break;
		}
	default:
		break;
	}
}

