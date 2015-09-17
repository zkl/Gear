#include "src/route/astar/astar.h"
#include "gamescreen.h"
#include <stdlib.h>
#include <time.h>

bool GameScreen::init()
{
	_tilemap.load("map.tmx");
	_robot.setTileMap(&_tilemap);

	_world.appendChild(&_tilemap);
	_world.appendChild(&_target);
	_world.appendChild(&_robot);
	_world.appendChild(&_bob);
	_world.init();

	_route.resize(_tilemap.colum(), _tilemap.row());

	Image image("target.png");
	_target.addFrames(&image, 0, 0, 16, 16, 6, 6);

	Image bobimg("bob.png");
	_bob.addFrames(&bobimg, 0, 0, 64, 64, 6, 6);
	_bob.setFps(15);
	
	_target.loop();
	_target.play();
	_target.setFps(15);

	srand(time(0));
	return true;
}

void GameScreen::update(unsigned int dt)
{
	_world.update(dt);
	
	if(!_robot.moving() && _route.way().size() > 0)
	{
		if(_robot.x() < _route.way()[0]->x*_tilemap.tilewidth())
			_robot.turnRight();
		else if(_robot.x() > _route.way()[0]->x*_tilemap.tilewidth())
			_robot.turnLeft();

		if(_robot.y() < _route.way()[0]->y*_tilemap.tileheight())
			_robot.turnDown();
		else if(_robot.y() > _route.way()[0]->y*_tilemap.tileheight())
			_robot.turnUp();

		_route.way().erase(_route.way().begin());

		if(_route.way().size() == 0)
		{

			int w = _tilemap.tilewidth();
			int h = _tilemap.tileheight();

			while(1)
			{
				int x = rand()%_tilemap.width();
				int y = rand()%_tilemap.height();
				while(_tilemap.getGid(x, y) != 0)
				{
					// 在附近生成目标
					x = rand()%(_tilemap.width()/4)+_robot.x()-_tilemap.width()/4;
					y = rand()%(_tilemap.height()/4)+_robot.y()-_tilemap.height()/4;
	
					x = x > _tilemap.width()? _tilemap.width() : x;
					y = y > _tilemap.height()? _tilemap.height() : y;
					x = x < 0? 0 : x;
					y = y < 0? 0 : y;
				}

				_target.setPosition(x-x%w, y-y%h);

				_route.begin (_robot.x()/w, _robot.y()/h);
				_route.target(_target.x()/w, _target.y()/w);

				_bob.setPosition(_robot.x()-32+8, _robot.y()-32+8);
				_bob.setVisiable();
				_bob.play();

				if(_route.find(&_tilemap))
					break;
			}
		}
	}

	if(!_bob.playing())
		_bob.setVisiable(false);
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
			int w = _tilemap.tilewidth();
			int h = _tilemap.tileheight();
			int x = event.motion.x;
			int y = event.motion.y;

			_target.setPosition(x-x%w, y-y%h);

			_route.begin (_robot.x()/w, _robot.y()/h);
			_route.target(_target.x()/w, _target.y()/w);
			_route.find(&_tilemap);

			break;
		}
		case SDL_MOUSEMOTION:
		{
			break;
		}
		case SDL_KEYDOWN:
		{
			const Uint8* sta = SDL_GetKeyboardState(0);

			if(sta[SDL_SCANCODE_W])
				_robot.turnUp();
			if(sta[SDL_SCANCODE_S])
				_robot.turnDown();
			if(sta[SDL_SCANCODE_A])
				_robot.turnLeft();
			if(sta[SDL_SCANCODE_D])
				_robot.turnRight();

			break;
		}
	default:
		break;
	}
}

