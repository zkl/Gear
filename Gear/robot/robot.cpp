#include "robot.h"

Robot::Robot() : 
	_uptime(0),
	_height(16),
	_width(16),
	_tilemap(0)
{
}

void Robot::turnLeft()
{
	if(_currentDirection == DIR_STOP)
		_currentDirection = DIR_LEFT;
	else
		_direction = DIR_LEFT;
}

void Robot::turnRight()
{
	if(_currentDirection == DIR_STOP)
		_currentDirection = DIR_RIGHT;
	else
		_direction = DIR_RIGHT;
}

void Robot::turnUp()
{
	if(_currentDirection == DIR_STOP)
		_currentDirection = DIR_UP;
	else
		_direction = DIR_UP;
}

void Robot::turnDown()
{
	if(_currentDirection == DIR_STOP)
		_currentDirection = DIR_DOWN;
	else
		_direction = DIR_DOWN;
}

void Robot::setTileMap(TileMap* tilemap)
{
	_tilemap = tilemap;
}

bool Robot::init()
{
	_speed = 12;
	_uptime = 0;

	_direction = DIR_STOP;
	_currentDirection = _direction;

	_image.load("block.png");

	return true;
}

void Robot::update(unsigned int dt)
{
	_uptime += dt;

	if(_uptime > _speed)
	{
		_uptime -= _speed;
		move();
	}
}

void Robot::draw(SDL_Renderer * renderer)
{
	_image.draw(renderer, _x, _y);
}

void Robot::move()
{
	if(!moving())
		return ;

	int x = _x, y = _y;
	_currentDirection == DIR_LEFT ? _x -= 1 : 0;
	_currentDirection == DIR_RIGHT ? _x += 1 : 0;
	_currentDirection == DIR_UP ? _y -= 1 : 0;
	_currentDirection == DIR_DOWN ? _y += 1 : 0;

	if(blocked() || (_x%_width == 0 && _y%_height == 0))
	{
		_currentDirection = _direction;
		_direction = DIR_STOP;
	}

	if(blocked())
	{
		_x = x;
		_y = y;
	}
}


bool Robot::blocked()
{
	int x1 = _x, y1 = _y;
	int x2 = _x+_width-1, y2 = _y+_height-1;
	if(_tilemap->getGid(x1, y1) == 0 && _tilemap->getGid(x2, y2) == 0)
		return false;
	
	return true;
}
