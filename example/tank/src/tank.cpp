#include "tank.h"

Tank::Tank() : 
	_moving(false),
	_uptime(0),
	_width(16),
	_height(16),
	_tilemap(0)
{
	for(int i=0; i<10; i++)
		_bullets.push_back(Bullet());

	for(unsigned int i=0; i<_bullets.size(); i++)
		this->appendChild(&_bullets[i]);
}

void Tank::turnLeft()
{
	_moving = true;
	_direction = DIR_LEFT;
}

void Tank::turnRight()
{
	_moving = true;
	_direction = DIR_RIGHT;
}

void Tank::turnUp()
{
	_moving = true;
	_direction = DIR_UP;
}

void Tank::turnDown()
{
	_moving = true;
	_direction = DIR_DOWN;
}

void Tank::fire()
{
	for(unsigned int i=0; i<_bullets.size(); i++)
	{
		if(!_bullets[i].actived())
		{
			_bullets[i].setPosition(_x, _y);
			_bullets[i].emit(_direction);
			break;
		}
	}
}

void Tank::setTileMap(TileMap* tilemap)
{
	_tilemap = tilemap;

	_width = _tilemap->tilsetWidth();
	_height = _tilemap->tilsetHeight();
}

bool Tank::init()
{
	_moving = false;
	_speed = 15;
	_step  = 1;
	_uptime = 0;
	_direction = DIR_UP;

	_image.load("tank.png");
	return Object::init();
}

void Tank::update(unsigned int dt)
{
	_uptime += dt;
	while(_uptime > _speed)
	{
		_uptime -= _speed;
		move();
	}
	Object::update(dt);

	for(unsigned int i=0; i<_bullets.size(); i++)
	{
		Bullet& bullet = _bullets[i];
		if(bullet.actived() && !bullet.bobing())
		{
			if(bullet.x() < 0 || bullet.x() > _tilemap->width() || 
			   bullet.y() < 0 || bullet.y() > _tilemap->height())
			{
				bullet.bob();
			}

			if(_tilemap->getGid(bullet.x(), bullet.y()) != 0 ||
			   _tilemap->getGid(bullet.x()+8, bullet.y()+8) != 0)
				bullet.bob();
		}
	}
}

void Tank::draw(SDL_Renderer * renderer)
{
	_image.draw(renderer, _x, _y);

	Object::draw(renderer);
}

void Tank::move()
{
	if(!_moving)
		return ;

	int x = _x, y = _y;
	if(_direction == DIR_LEFT)
	{
		_image.rotation(270);
		_x -= _step;
	}
	else if(_direction == DIR_RIGHT)
	{
		_image.rotation(90);
		_x += _step;
	}
	else if(_direction == DIR_UP)
	{
		_image.rotation(0);
		_y -= _step;
	}
	else if(_direction == DIR_DOWN)
	{
		_image.rotation(180);
		_y += _step;
	}
	
	if(blocked() || (_x%_width == 0 && _y%_height == 0))
	{
		_moving = false;
		if(blocked())
		{
			_x = x;
			_y = y;
		}
	}
}


bool Tank::blocked()
{
	int x1 = _x, y1 = _y;
	int x2 = _x+_width-1, y2 = _y+_height-1;
	if(_tilemap->getGid(x1, y1) == 0 && _tilemap->getGid(x2, y2) == 0)
		return false;
	
	return true;
}
