#ifndef ROBOT_H
#define ROBOT_H

#include "src/object.h"
#include "src/image.h"
#include "src/tilemap/tilemap.h"

class Tank : public Object
{
public: 
	Tank();
	
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
	int _step;
	int _uptime;

	int _width;
	int _height;
	Image _image;
	TileMap* _tilemap;
};


inline void Tank::setGridSize(int width, int height)
{
	_width = width;
	_height = height;
}

inline bool Tank::moving()
{
	return _currentDirection != DIR_STOP;
}

#endif
