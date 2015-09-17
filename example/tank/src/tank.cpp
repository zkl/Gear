#include "src/event/eventhandler.h"
#include "src/director.h"
#include "tank.h"

Tank::Tank() : 
	_explorer(true),
	_moving(false),
	_group(0),
	_uptime(0),
	_width(16),
	_height(16),
	_tilemap(0)
{
	_unuserdBullets.reserve(3);
	_bullets.reserve(3);

	for(int i=0; i<5; i++)
		_unuserdBullets.push_back(new Bullet());

	for(unsigned int i=0; i<_unuserdBullets.size(); i++)
		this->appendChild(_unuserdBullets[i]);
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
	if(_unuserdBullets.size() == 0)
		return ;

	Bullet* bullet = _unuserdBullets[0];
	bullet->setPosition(_x, _y);
	bullet->launch(_direction);

	_unuserdBullets.erase(_unuserdBullets.begin());
	_bullets.push_back(bullet);
}

void Tank::setTileMap(TileMap* tilemap)
{
	_tilemap = tilemap;

	_width = _tilemap->tilewidth();
	_height = _tilemap->tileheight();
}

bool Tank::init()
{
	_explorer = true;
	_moving = false;
	_speed = 1000/60;
	_step  = 2;
	_uptime = 0;
	_direction = DIR_UP;

	if(_group == 0)
		_image.load("tank_red.png");
	else
		_image.load("tank.png");

	return Object::init();
}

void Tank::update(unsigned int dt)
{
	_uptime += dt;
	if(_uptime > _speed)
	{
		_uptime = 0;
		if(_moving)
			this->move();
	}

	Object::update(dt);

	for(std::vector<Bullet*>::iterator it = _bullets.begin(); it !=_bullets.end();)
	{
		Bullet& bullet = *(*it);
		if(bullet.actived() && !bullet.exploding())
		{
			if(bullet.x() < 0 || bullet.x()+15 > _tilemap->width() || 
			   bullet.y() < 0 || bullet.y()+15 > _tilemap->height())
			{
				bullet.explode();
			}

			int gid =_tilemap->getGid(bullet.x(), bullet.y());
			if(gid != 0)
			{
				if(++gid > 4)
					gid = 0;
				_tilemap->setGid(bullet.x(), bullet.y(), gid);
				bullet.explode();
			}

			gid = _tilemap->getGid(bullet.x()+15, bullet.y()+15);
			if( gid != 0)
			{
				if(++gid > 4)
					gid = 0;

				_tilemap->setGid(bullet.x()+15, bullet.y()+15, gid);
				bullet.explode();
			}

			int position = _tilemap->convertPositionFromCoordinate(bullet.x(), bullet.y());
			Tank* tank = (Tank*)_tilemap->getObject(position);
			if(tank != 0 && tank->getGroup() != this->getGroup())
			{
				bullet.explode();
				tank->blowUp();
			}

			it++;
		}
		else
		{
			_unuserdBullets.push_back(*it);
			it = _bullets.erase(it);
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

	if(_explorer)
	{
		if(blocked())
		{
			_x = x;
			_y = y;
		}
		else
		{
			int p2 = _tilemap->convertPositionFromCoordinate(_x, _y);
			int p3 = _tilemap->convertPositionFromCoordinate(_x+15, _y+15);
			_tilemap->setObject(p2, this);
			_tilemap->setObject(p3, this);
		}
	}

	_explorer = false;
	if(_x%_width == 0 && _y%_height == 0)
	{
		_explorer = true;
		_moving = false;

		int p0 = _tilemap->convertPositionFromCoordinate(x, y);
		int p1 = _tilemap->convertPositionFromCoordinate(x+15, y+15);
		_tilemap->setObject(p0, 0);
		_tilemap->setObject(p1, 0);

		int p2 = _tilemap->convertPositionFromCoordinate(_x, _y);
		_tilemap->setObject(p2, this);
	}
}



bool Tank::blocked()
{
	int x1 = _x, y1 = _y;
	int x2 = _x+_width, y2 = _y+_height;

	if(x1 < 0 || y1 < 0 || x2 > _tilemap->width() || y2 > _tilemap->height())
		return true;

	int p = _tilemap->convertPositionFromCoordinate(_x, _y);
	Tank* tank = (Tank*)_tilemap->getObject(p);
	if(tank != this && tank != 0)
		return true;

	if(_tilemap->getGid(x1, y1) == 0 && _tilemap->getGid(x2-1, y2-1) == 0)
		return false;

	return true;
}

void Tank::blowUp()
{
	this->setVisiable(false);
	this->setActive(false);
	this->unmarkOnMap();

	EventHandler::instance()->dispatch(0, this);
}

void Tank::unmarkOnMap()
{
	int p1 = _tilemap->convertPositionFromCoordinate(_x, _y);
	int p2 = _tilemap->convertPositionFromCoordinate(_x+15, _y+15);
	_tilemap->setObject(p1, 0);
	_tilemap->setObject(p2, 0);
}
