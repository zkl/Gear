#include "tank.h"
#include "bullet.h"

Bullet::Bullet() : 
	_explorer(false),
	_exploding(false),
	_step(8),
	_uptime(0)
{
	_bomb.setFps(15);

	Image bombImage("bob.png");
	_bomb.addFrames(&bombImage, 0, 0, 64, 64, 5, 5);

	this->setActive(false);
	this->setVisiable(false);

	this->appendChild(&_bomb);
	_image.load("bullet.png");
}

void Bullet::launch(int direction)
{
	_bomb.setVisiable(false);

	this->setVisiable();
	this->setActive();

	_direction = direction;
	if(_direction == DIR_RIGHT)
		_image.rotation(0);
	else if(_direction == DIR_LEFT)
		_image.rotation(180);
	else if(_direction == DIR_UP)
		_image.rotation(270);
	else 
		_image.rotation(90);
}

void Bullet::explode()
{
	_exploding = true;

	_bomb.setPosition(_x-32+8, _y-32+8);
	_bomb.setActive();
	_bomb.setVisiable();
	_bomb.play();
}

void Bullet::draw(SDL_Renderer * renderer)
{
	if(!_exploding)
		_image.draw(renderer, _x, _y);
	else 
		Object::draw(renderer);
}

void Bullet::update(unsigned int dt)
{
	Object::update(dt);

	if(_exploding)
	{
		if(!_bomb.playing())
		{
			_exploding = false;

			_bomb.setActive(false);
			_bomb.setVisiable(false);

			this->setActive(false);
			this->setVisiable(false);
		}
		else
		{
			// bomb playing
		}
	}
	else
	{
		if(_direction == DIR_RIGHT)
			_x += _step;
		else if(_direction == DIR_LEFT)
			_x -= _step;
		else if(_direction == DIR_UP)
			_y -= _step;
		else 
			_y += _step;
	}
}


