#include "bullet.h"

Bullet::Bullet() : 
	_uptime(0),
	_interval(5)
{
}

void Bullet::emit(int direction)
{
	_direction = direction;

	this->setVisiable();
	this->setActive();
}

bool Bullet::init()
{
	_image.load("bullet.png");
	return !_image.empty();
}

void Bullet::draw(SDL_Renderer * renderer)
{
	_image.draw(renderer, _x, _y);
}

void Bullet::update(unsigned int dt)
{
	_uptime += dt;
	while(_uptime > _interval)
	{
		_uptime -= _interval;
		switch(_direction)
		{
		case 0:
			_x += 1;
			break;
		case 1:
			_x -= 1;
			break;
		case 2:
			_y += 1;
			break;
		case 3:
			_y -= 1;
			break;
		}
	}
}


