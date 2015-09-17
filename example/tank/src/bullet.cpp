#include "tank.h"
#include "bullet.h"

Bullet::Bullet() : 
	_explorer(false),
	_exploding(false),
	_step(4),
	_uptime(0)
{
	_bomb.setActive(false);
	_bomb.setVisiable(false);
	this->setActive(false);
	this->setVisiable(false);
}

void Bullet::launch(int direction)
{
	this->setVisiable();
	this->setActive();
	_direction = direction;

	switch(_direction)
	{
	case DIR_RIGHT:
		_image.rotation(0);
		break;
	case DIR_LEFT:
		_image.rotation(180);
		break;
	case DIR_DOWN:
		_image.rotation(90);
		break;
	case DIR_UP:
		_image.rotation(270);
		break;
	default:
		break;
	}
}

void Bullet::explode()
{
	_exploding = true;
	_bomb.setPosition(_x-32+8, _y-32+8);
	_bomb.setActive();
	_bomb.setVisiable();
	_bomb.play();
}

bool Bullet::init()
{
	Image bombImage("bob.png");
	_bomb.addFrames(&bombImage, 0, 0, 64, 64, 5, 5);
	this->appendChild(&_bomb);

	_bomb.setActive(false);
	_bomb.setVisiable(false);
	_bomb.setFps(15);

	this->setActive(false);
	this->setVisiable(false);

	_image.load("bullet.png");

	return !_image.empty();
}

void Bullet::draw(SDL_Renderer * renderer)
{
	if(!_exploding)
		_image.draw(renderer, _x, _y);

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
		return ;
	}

	switch(_direction)
	{
	case DIR_RIGHT:
		_x += _step;
		break;
	case DIR_LEFT:
		_x -= _step;
		break;
	case DIR_DOWN:
		_y += _step;
		break;
	case DIR_UP:
		_y -= _step;
		break;
	default:
		break;
	}
}


