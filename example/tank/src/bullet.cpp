#include "tank.h"
#include "bullet.h"

Bullet::Bullet() : 
	_bobing(false),
	_interval(5),
	_uptime(0)
{
	_bob.setActive(false);
	_bob.setVisiable(false);
}

void Bullet::emit(int direction)
{
	this->setVisiable();
	this->setActive();

	_direction = direction;
	
	if(_direction == DIR_RIGHT)
		_image.rotation(0);
	else if(_direction == DIR_LEFT)
		_image.rotation(180);
	else if(_direction == DIR_UP)
		_image.rotation(270);
	else if(_direction == DIR_DOWN)
		_image.rotation(90);
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
	_bob.setFps(10);

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

			_bob.setActive(false);
			_bob.setVisiable(false);

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
		case DIR_RIGHT:
			_x += 1;
			break;
		case DIR_LEFT:
			_x -= 1;
			break;
		case DIR_DOWN:
			_y += 1;
			break;
		case DIR_UP:
			_y -= 1;
			break;
		default:
			break;
		}
	}

}


