#include "bullet.h"

Bullet::Bullet() : 
	_uptime(0),
	_interval(5),
	_bobing(false)
{
}

void Bullet::emit(int direction)
{
	_direction = direction;

	this->setVisiable();
	this->setActive();
}

void Bullet::bob()
{
	_bobing = true;
	_bob.setPosition(_x-32+8, _y-32+8);
	_bob.setActive();
	_bob.setVisiable();
	_bob.play();
}

bool Bullet::init()
{
	Image bobimg("bob.png");
	_bob.addFrames(&bobimg, 0, 0, 64, 64, 5, 5);
	this->appendChild(&_bob);

	_bob.setActive(false);
	_bob.setVisiable(false);
	_bob.setFps(5);

	_image.load("bullet.png");
	return !_image.empty();
}

void Bullet::draw(SDL_Renderer * renderer)
{
	if(!_bobing)
		_image.draw(renderer, _x, _y);

	Object::draw(renderer);
}

void Bullet::update(unsigned int dt)
{
	Object::update(dt);
	if(_bobing)
	{
		if(!_bob.playing())
		{
			_bobing = false;
			this->setActive(false);
			this->setVisiable(false);
		}
		return ;
	}

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


