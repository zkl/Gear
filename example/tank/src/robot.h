#ifndef ROBOT_H
#define ROBOT_H

#include "src/object.h"
#include "src/route/astar/astar.h"
#include "tank.h"

class Robot : public Object
{
public:
	Robot();

	void setMap(TileMap* map);
	virtual bool init();
	virtual void update(unsigned int dt);

private:
	int _uptime;
	Tank _tank;
	AStar _route;

};

inline Robot::Robot()
{
	_tank.setGroup(1);
	this->appendChild(&_tank);
}

inline void Robot::setMap(TileMap* map)
{
	_tank.setTileMap(map);
	_route.resize(map->colum(), map->row());
}

inline bool Robot::init()
{
	_uptime = rand()%8000+1000;
	return Object::init();
};

inline void Robot::update(unsigned int dt)
{
	if(!_tank.moving())
	{
		int times = 0; // A* Ñ°Â·´ÎÊı
		while((_route.way().size() == 0) && times > 0)
		{
			TileMap* tilemap = _tank.tilemap();
			_route.begin(_tank.x()/tilemap->tilewidth(), _tank.y()/tilemap->tileheight());
			_route.target(rand()%tilemap->colum(), rand()%tilemap->row());
			if(_route.find(tilemap))
				break;

			times--;
		}

		if(_route.way().size() > 0)
		{
			int x = _route.way()[0]->x * _tank.tilemap()->tilewidth();
			int y = _route.way()[0]->y * _tank.tilemap()->tileheight();

			if(_tank.x() < x)
				_tank.turnRight();
			else if(_tank.x() > x)
				_tank.turnLeft();
			else if(_tank.y() < y)
				_tank.turnDown();
			else if(_tank.y() > y)
				_tank.turnUp();
			else 
				_route.way().erase(_route.way().begin());
		}
		else
		{
			if(rand()%100 < 20)
				_tank.turn((Direction)(rand()%4));

			_tank.moveForword();
		}
	}

	_uptime -= dt;
	if(_uptime < 0)
	{
		_uptime = rand()%3000+500;
		_tank.fire();
	}

	Object::update(dt);
}

#endif
