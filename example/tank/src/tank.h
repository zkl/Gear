#ifndef TANK_H 
#define TANK_H 

#include "src/object.h"
#include "src/image.h"
#include "src/tilemap/tilemap.h"
#include "bullet.h"

enum Direction
{
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_DOWN,
	DIR_STOP
};

#define MAX_WEAPON_LEVEL 5
#define MAX_LEVEL 3

class Tank : public Object
{
public: 
	Tank();
	
	void fire();
	void explode();

	void relocation(int x, int y);
	void reborn();
	bool lived();
	void upgrade();

	void turnLeft();
	void turnRight();
	void turnUp();
	void turnDown();

	void setGroup(int group);
	int  getGroup();

	void moveForword();
	void turn(Direction direction);
	Direction direction();

	bool moving();
	void setTileMap(TileMap* tilemap);
	TileMap* map();

	virtual void draw(SDL_Renderer * renderer);
	virtual void update(unsigned int dt);

private:
	void markObjectOnMap(int x, int y, void* object = 0);
	void move();
	bool blocked();

	void initData();

	bool _alive;
	bool _explorer;
	bool _moving;

	int _speed;
	int _level;
	int _weaponsLevel;

	int _group;
	int _width;
	int _height;

	Image _image;
	Movie _bomb;
	Direction _direction;
	TileMap* _tilemap;
	std::vector<Bullet*> _bullets;
	std::vector<Bullet*> _surplusBullets;
};

inline void Tank::initData()
{
	_alive = true;
	_moving = false;
	_explorer = true;
	_speed = 1;

	_level = 0;
	_weaponsLevel = 1;
}

inline void Tank::upgrade()
{
	if(_weaponsLevel < MAX_WEAPON_LEVEL)
		_weaponsLevel++;

	if(_level < MAX_LEVEL)
		_level++;

	_speed = _level*2;
}

inline bool Tank::lived()
{
	return _alive;
}

inline bool Tank::moving()
{
	return _moving;
}

inline TileMap* Tank::map()
{
	return _tilemap;
}

inline Direction Tank::direction()
{
	return _direction;
}

inline void Tank::turn(Direction direction)
{
	_direction = direction;
	if(_direction == DIR_LEFT)
		_image.rotation(270);
	else if(_direction == DIR_RIGHT)
		_image.rotation(90);
	else if(_direction == DIR_UP)
		_image.rotation(0);
	else if(_direction == DIR_DOWN)
		_image.rotation(180);
}

inline void Tank::moveForword()
{
	_moving = true;
}

inline void Tank::setGroup(int group)
{
	_group = group;

	if(_group == 1)
		_image.load("tank.png");
}

inline int  Tank::getGroup()
{
	return _group;
}

#endif
