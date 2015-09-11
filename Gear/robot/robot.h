#ifndef ROBOT_H
#define ROBOT_H

#include "../src/object.h"
#include "../src/image.h"
#include "../src/tilemap/tilemap.h"

class Robot : public Object
{
public: 
	Robot();
	
	void turnLeft();
	void turnRight();
	void turnUp();
	void turnDown();

	bool moving();
	void setTileMap(TileMap* tilemap);
	void setGridSize(int width, int height);
	virtual void draw(SDL_Renderer * renderer);
	virtual bool init();
	virtual void update(unsigned int dt);

private:
	void move();
	bool blocked();

	enum Direction
	{
		DIR_LEFT,
		DIR_RIGHT,
		DIR_UP,
		DIR_DOWN,
		DIR_STOP
	};

	Direction _direction;
	Direction _currentDirection;

	int _speed;
	int _uptime;

	int _width;
	int _height;
	Image _image;
	TileMap* _tilemap;
};


inline void Robot::setGridSize(int width, int height)
{
	_width = width;
	_height = height;
}


inline void Robot::draw(SDL_Renderer * renderer)
{
	_image.draw(renderer, _x, _y);
}

inline bool moving()
{
	return _currentDirection == DIR_STOP && _direction == DIR_STOP;
}

#endif
