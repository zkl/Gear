#ifndef SNAKE_H
#define SNAKE_H

#include "../src/object.h"
#include "../src/image.h"

class Snake : public Object
{
public: 
	Snake();
	void uplevel();
	int  level() const;
	bool dead();
	void turnLeft();
	void turnRight();
	void turnUp();
	void turnDown();

	void setGridSize(int width, int height);
	virtual void draw(SDL_Renderer * renderer);
	virtual bool init();
	virtual void update(unsigned int dt);

private:
	void move();

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

	int _level;
	int _speed;
	int _uptime;
	bool _dead;

	struct SnakeNode
	{
		int x;
		int y;
		Image* image;
	};

	int _gridWidth;
	int _gridHeight;
	Image _image;
	std::vector<SnakeNode> _snake;
};

inline Snake::Snake() : 
	_uptime(0),
	_gridHeight(16),
	_gridWidth(16)
{
}
inline void Snake::uplevel()
{
	_level++;
	_speed -= 10;
	if(_speed <= 0)
		_speed = 1;

	SnakeNode node = _snake[_snake.size()-1];
	_snake.push_back(node);
}

inline int  Snake::level() const
{
	return _level;
}

inline bool Snake::dead()
{
	return _dead;
}

inline void Snake::turnLeft()
{
	if(_currentDirection != DIR_RIGHT)
		_direction = DIR_LEFT;
}

inline void Snake::turnRight()
{
	if(_currentDirection != DIR_LEFT)
		_direction = DIR_RIGHT;
}

inline void Snake::turnUp()
{
	if(_currentDirection != DIR_DOWN)
		_direction = DIR_UP;
}

inline void Snake::turnDown()
{
	if(_currentDirection != DIR_UP)
		_direction = DIR_DOWN;
}

inline bool Snake::init()
{
	_speed = 140;
	_level = 1;
	_uptime = 0;
	_dead = false;

	_snake.clear();
	_direction = DIR_RIGHT;
	_currentDirection = _direction;
	_image.load("block.png");

	SnakeNode node;
	node.x = _x;
	node.y = _y;
	node.image = &_image;

	_snake.push_back(node); // head

	return true;
}

inline void Snake::setGridSize(int width, int height)
{
	_gridWidth = width;
	_gridHeight = height;
}

inline void Snake::update(unsigned int dt)
{
	_uptime += dt;

	if(_uptime > _speed)
	{
		_uptime -= _speed;
		move();
	}
}

inline void Snake::draw(SDL_Renderer * renderer)
{
	for(unsigned int i=0; i<_snake.size(); i++)
	{
		SnakeNode& node = _snake[i];
		node.image->draw(renderer, node.x, node.y);
	}
}

inline void Snake::move()
{
	for(int i=_snake.size()-1; i>0; i--)
	{
		_snake[i].x = _snake[i-1].x;
		_snake[i].y = _snake[i-1].y;
	}


	if(_currentDirection == DIR_LEFT)
		_snake[0].x -= _gridWidth;
	else if(_currentDirection == DIR_RIGHT)
		_snake[0].x += _gridWidth;
	else if(_currentDirection == DIR_UP)
		_snake[0].y -= _gridHeight;
	else
		_snake[0].y += _gridHeight;

	if(_snake[0].x%_gridWidth == 0 && _snake[0].y%_gridHeight == 0)
	{
		for(unsigned int i=1; i<_snake.size(); i++)
		{
			if(_snake[i].x == _snake[0].x && _snake[i].y == _snake[0].y)
				_dead = true;
		}
	}

	_currentDirection = _direction;
	this->setPosition(_snake[0].x, _snake[0].y);
}

#endif
