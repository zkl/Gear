#ifndef ROBOT_H
#define ROBOT_H

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
	
	void turnLeft();
	void turnRight();
	void turnUp();
	void turnDown();
	void fire();

	void moveForword();
	void turn(Direction direction);
	Direction direction();

	bool moving();
	void setTileMap(TileMap* tilemap);

	virtual void draw(SDL_Renderer * renderer);
	virtual bool init();
	virtual void update(unsigned int dt);

private:
	void move();
	bool blocked();

	bool _moving;
	Direction _direction;

	int _speed;
	int _step;
	int _uptime;

	int _width;
	int _height;

	Image _image;
	TileMap* _tilemap;
	std::vector<Bullet> _bullets;
};

inline bool Tank::moving()
{
	return _moving;
}

inline Direction Tank::direction()
{
	return _direction;
}

#endif
