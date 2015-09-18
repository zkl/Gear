#include <assert.h>
#include "src/event/eventhandler.h"
#include "src/director.h"
#include "tank.h"

Tank::Tank() : 
	_group(0),
	_width(16),
	_height(16),
	_tilemap(0),
	_direction(DIR_DOWN)
{
	this->initData();

	_surplusBullets.reserve(MAX_WEAPON_LEVEL);
	_bullets.reserve(MAX_WEAPON_LEVEL);

	for(int i=0; i<MAX_WEAPON_LEVEL; i++)
		_surplusBullets.push_back(new Bullet());

	for(unsigned int i=0; i<_surplusBullets.size(); i++)
		this->appendChild(_surplusBullets[i]);

	_image.load("tank_red.png");
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
	if(_bullets.size() < (unsigned int)_weaponsLevel)
	{
		Bullet* bullet = _surplusBullets[0];
		bullet->setPosition(_x, _y);
		bullet->launch(_direction);

		_surplusBullets.erase(_surplusBullets.begin());
		_bullets.push_back(bullet);
	}
}

void Tank::setTileMap(TileMap* tilemap)
{
	_tilemap = tilemap;
}

void Tank::update(unsigned int dt)
{
	if(_moving && _alive)
		this->move();

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
			Tank* tank = (Tank*)_tilemap->getObjectLayer()->getObject(position);
			if(tank != 0 && tank->getGroup() != this->getGroup())
			{
				bullet.explode();
				tank->explode();
			}
			it++;
		}
		else
		{
			_surplusBullets.push_back(*it);
			it = _bullets.erase(it);
		}
	}

	if(!_alive && _bullets.size() == 0)
	{
		this->setVisiable(false);
		this->setActive(false);
		this->markObjectOnMap(_x, _y, 0); // clear 
		EventHandler::instance()->dispatch(0, this);
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
		_x -= _speed;
	}
	else if(_direction == DIR_RIGHT)
	{
		_image.rotation(90);
		_x += _speed;
	}
	else if(_direction == DIR_UP)
	{
		_image.rotation(0);
		_y -= _speed;
	}
	else if(_direction == DIR_DOWN)
	{
		_image.rotation(180);
		_y += _speed;
	}

	if(x < 0 || y < 0)
	{
		assert(x >= 0);
		assert(y >= 0);
		printf("Tank::move -> Error Position");
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
			int p1 = _tilemap->convertPositionFromCoordinate(_x, _y);
			int p2 = _tilemap->convertPositionFromCoordinate(_x+15, _y+15);
			Tank* tank1 = (Tank*)_tilemap->getObjectLayer()->getObject(p1);
			Tank* tank2 = (Tank*)_tilemap->getObjectLayer()->getObject(p2);
			if(tank1 != this && tank1 != 0 || tank2 != this && tank2 != 0)
			{
				_x = x;
				_y = y;
			}
			else
			{
				this->markObjectOnMap(_x, _y, this);
			}
		}
	}

	_explorer = false;
	if(_x%_tilemap->tilewidth() == 0 && _y%_tilemap->tileheight() == 0)
	{
		_explorer = true;
		_moving   = false;

		this->markObjectOnMap(x, y, 0);
		this->markObjectOnMap(_x, _y, this);
	}
}


bool Tank::blocked()
{
	int x1 = _x, y1 = _y;
	int x2 = _x+_image.width(), y2 = _y+_image.height();

	if(x1 < 0 || y1 < 0 || x2 > _tilemap->width() || y2 > _tilemap->height())
		return true;

	int p = _tilemap->convertPositionFromCoordinate(_x, _y);
	Tank* tank = (Tank*)_tilemap->getObjectLayer()->getObject(p);
	if(tank != this && tank != 0)
		return true;

	if(_tilemap->getGid(x1, y1) == 0 && _tilemap->getGid(x2-1, y2-1) == 0)
		return false;

	return true;
}

void Tank::explode()
{
	_alive = false;
	this->markObjectOnMap(_x, _y, 0); // clear 
	for(unsigned int i=0; i<_bullets.size(); i++)
		_bullets[i]->explode();
}

void Tank::relocation(int x, int y)
{
	this->markObjectOnMap(_x, _y, 0);

	_x = x/_tilemap->tilewidth()  * _tilemap->tilewidth();
	_y = y/_tilemap->tileheight() * _tilemap->tileheight();

	assert(_x >= 0);
	assert(_y >= 0);

	this->markObjectOnMap(_x, _y, 0);
}

void Tank::reborn()
{
	this->initData();

	this->setVisiable(true);
	this->setActive(true);
	this->markObjectOnMap(_x, _y, this);
}

void Tank::markObjectOnMap(int x, int y, void* object)
{
	if(_tilemap)
	{
		int p1 = _tilemap->convertPositionFromCoordinate(x, y);
		int p2 = _tilemap->convertPositionFromCoordinate(x+15, y+15);
		_tilemap->getObjectLayer()->setObject(p1, object);

		if(p1 != p2)
			_tilemap->getObjectLayer()->setObject(p2, object);
	}
}
