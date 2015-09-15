#include "control.h"

void Control::update(int dt)
{
	std::vector<Bullet*>::iterator it = _bullets.begin();
	for(it = _bullets.begin(); it != _bullets.end();)
	{
		Bullet* bullet = *it;
		if(!bullet->actived())
		{
			_unuserdBullets.push_back(bullet);
			it = _bullets.erase(it);
		}
		else
		{
			it++;
		}

		if(bullet->x() < 0 || bullet->x() > _tilemap->width())
		{
			bullet->setVisiable(false);
			bullet->setActive(false);
		}
		else
		{
			int gid = _tilemap->getGid(bullet->x(), bullet->y());
			if(gid != 0)
				bullet->bob();
		}
	}

	for(unsigned int i=0; i<_tanks.size(); i++)
	{
		Tank* tank = _tanks[i];
		if(rand()%100 >= 99)
		{
			Bullet* bullet = _unuserdBullets.size() > 0? _unuserdBullets[0] : new Bullet();
			if(_unuserdBullets.size() > 0)
			{
				bullet = _unuserdBullets[0];
				_unuserdBullets.erase(_unuserdBullets.begin());
			}
			else
			{

				bullet = new Bullet();
				bullet->init();
				_world->appendChild(bullet);
			}

			bullet->setPosition(tank->x(), tank->y());
			bullet->emit(0);
			_bullets.push_back(bullet);
		}
	}
}

void Control::createTank(int x, int y)
{
	Tank* tank = new Tank();
	tank->init();
	tank->setPosition(x, y);

	_tanks.push_back(tank);
	_world->appendChild(tank);
}
