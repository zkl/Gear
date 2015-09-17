#include "src/route/astar/astar.h"
#include "src/director.h"
#include "gamescreen.h"
#include <stdlib.h>
#include "src/event/eventhandler.h"

bool GameScreen::init()
{
	EventHandler::instance()->setMaxEventId(10);
	EventHandler::instance()->addEventWather(0, tankBlowUp, this);
	
	_tilemap.load("map.tmx");

	_world.appendChild(&_tilemap);
	_world.appendChild(&_tank);

	_livedTanks = 20;
	for(unsigned int i=0; i<_livedTanks; i++)
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

void GameScreen::begin()
{
	for(unsigned int i=0; i<_robots.size(); i++)
		_robots[i]->reset();

	_livedTanks = _robots.size();
	_tank.setVisiable();
	_tank.setActive();
}

void GameScreen::end()
{
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

bool GameScreen::tankBlowUp(int id, void* data, void* param)
{
	GameScreen* screen = (GameScreen*)data;
	Tank* tank = (Tank*)param;

	if(tank == &screen->_tank)
		Director::getDirector()->changeScreen("GameOver");
	else 
		screen->_livedTanks--;

	if(screen->_livedTanks <= 0)
	{
		SDL_Log("You Win");
	}
	return true;
}
