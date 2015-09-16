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

class Tank : public Object
{
public: 
	Tank();
	
	void fire();
	void blowUp();

	void setGroup(int group);
	int  getGroup();

	void turnLeft();
	void turnRight();
	void turnUp();
	void turnDown();

	void moveForword();
	void turn(Direction direction);
	Direction direction();

	bool moving();
	void setTileMap(TileMap* tilemap);
	TileMap* tilemap();

	virtual void draw(SDL_Renderer * renderer);
	virtual bool init();
	virtual void update(unsigned int dt);

private:
	void move();
	bool blocked();

	bool _explorer;
	bool _updatePosition;
	bool _moving;
	Direction _direction;

	int _group;
	int _speed;
	int _step;
	int _uptime;

	int _width;
	int _height;

	Image _image;
	TileMap* _tilemap;
	std::vector<Bullet*> _bullets;
	std::vector<Bullet*> _unuserdBullets;
};

inline bool Tank::moving()
{
	return _moving;
}

inline TileMap* Tank::tilemap()
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
}

inline void Tank::moveForword()
{
	_moving = true;
}

inline void Tank::setGroup(int group)
{
	_group = group;
}

inline int  Tank::getGroup()
{
	return _group;
}

#endif
