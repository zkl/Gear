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

	void patrol();

	virtual bool init();
	virtual void update(unsigned int dt);

private:
	int _uptime;
	Tank _tank;
	AStar _route;

};

inline Robot::Robot()
{
	this->appendChild(&_tank);
}

inline void Robot::setMap(TileMap* map)
{
	_tank.setTileMap(map);
	_route.resize(map->tilsetColum(), map->tilsetRow());
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
		int times = 10;
		while((_route.way().size() == 0) && times > 0)
		{
			TileMap* tilemap = _tank.tilemap();
			_route.begin(_tank.x()/tilemap->tilsetWidth(), _tank.y()/tilemap->tilsetHeight());
			_route.target(rand()%tilemap->tilsetColum(), rand()%tilemap->tilsetRow());
			if(_route.find(tilemap))
				break;

			times--;
		}

		if(_route.way().size() > 0)
		{
			int x = _route.way()[0]->x * _tank.tilemap()->tilsetWidth();
			int y = _route.way()[0]->y * _tank.tilemap()->tilsetHeight();

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