#include "src/route/astar/astar.h"
#include "src/director.h"
#include "gamescreen.h"
#include <stdlib.h>
#include "src/event/eventhandler.h"

#define MAX_TANKS_ONCE 10

GameScreen::GameScreen() : 
	_uptime(0),
	_level(0)
{	
}

bool GameScreen::init()
{
	EventHandler::instance()->setMaxEventId(10);
	EventHandler::instance()->addEventWather(0, watchTankBlowUp, this);
	
	_world.appendChild(&_tilemap);
	_world.appendChild(&_tank);
	_world.appendChild(&_robot);

	for(int i=0; i<MAX_TANKS_ONCE / 2; i++)
	{
		Tank* tank = new Tank();

		tank->upgrade();
		tank->setTileMap(&_tilemap);
		tank->setGroup(1);

		_robot.add(tank);
	}

	for(int i=0; i<MAX_TANKS_ONCE / 2; i++)
	{
		Tank* tank = new Tank();

		tank->upgrade();
		tank->setTileMap(&_tilemap);
		tank->setGroup(2);

		_robot.add(tank);
	}

	_robot.addRebornLocation(0, 0, DIR_DOWN);
	_robot.addRebornLocation(238, 0, DIR_DOWN);
	_robot.addRebornLocation(624, 0, DIR_DOWN);

	_tank.setPosition(160, 160);
	_tank.setTileMap(&_tilemap);

	_tank.upgrade();

	return true;
}

void GameScreen::begin()
{
	_uptime = 0;
	_lived  = MAX_TANKS_ONCE;
	_max    = 50;

	char mapfile[1024];
	sprintf(mapfile, "maps/level%d.tmx", _level);
	if(!_tilemap.load(mapfile))
	{
		Director::getDirector()->changeScreen("Menu");
	}
	else
	{
		_robot.rebornAllTanks();

		if(!_tank.lived())
		{
			_tank.reborn();
			_tank.upgrade();
		}

		_tank.relocation((_tilemap.colum()-4)/2 * _tilemap.tilewidth(), _tilemap.height() - _tilemap.tileheight());
		_tank.turn(DIR_UP);
	}
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
		if(sta[::SDL_SCANCODE_W] || sta[::SDL_SCANCODE_UP])
			_tank.turnUp();
		else if(sta[::SDL_SCANCODE_S] || sta[SDL_SCANCODE_DOWN])
			_tank.turnDown();
		else if(sta[::SDL_SCANCODE_A] || sta[SDL_SCANCODE_LEFT])
			_tank.turnLeft();
		else if(sta[::SDL_SCANCODE_D] || sta[SDL_SCANCODE_RIGHT])
			_tank.turnRight();
	}

	_uptime += dt;
	if(_uptime > 2000 && _lived < MAX_TANKS_ONCE && _lived < _max)
	{
		_uptime = 0;

		_lived++;
		_robot.randRebornATank();
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
			if(event.key.keysym.scancode == SDL_SCANCODE_SPACE)
				_tank.fire();

			if(event.key.keysym.scancode == SDL_SCANCODE_P)
				_robot.setActive(false);
			
			if(event.key.keysym.scancode == SDL_SCANCODE_G)
				_robot.setActive();

			break;
		}
	default:
		break;
	}
}

bool GameScreen::watchTankBlowUp(int , void* data, void* param)
{
	GameScreen* screen = (GameScreen*)data;
	Tank* tank = (Tank*)param;

	if(tank == &screen->_tank)
	{
		screen->_level = 0;
		Director::getDirector()->changeScreen("GameOver");
	}
	else 
	{
		screen->_max--;
		screen->_lived--;
	}

	if(screen->_max <= 0)
		Director::getDirector()->changeScreen("Win");

	return true;
}
