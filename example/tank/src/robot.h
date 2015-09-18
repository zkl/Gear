#ifndef ROBOT_H
#define ROBOT_H

#include "src/object.h"
#include "src/route/astar/astar.h"
#include "tank.h"

class Robot : public Object
{
public:
	Robot();

	void add(Tank* tank);
	void addRebornLocation(int x, int y, Direction direction);
	void randRebornATank(); 
	void rebornAllTanks();

	virtual void update(unsigned int dt);
private:
	struct Location
	{
		int x;
		int y;
		Direction direction;
	};

	std::vector<Location> _locations;
	std::vector<Tank* > _tanks;
};

inline Robot::Robot()
{
}

inline void Robot::add(Tank* tank)
{
	_tanks.push_back(tank);
	this->appendChild(tank);
}

inline void Robot::addRebornLocation(int x, int y, Direction direction)
{
	Location location;
	location.x = x;
	location.y = y;
	location.direction = direction;

	_locations.push_back(location);
}

inline void Robot::randRebornATank()
{
	for(unsigned int i=0; i<_tanks.size(); i++)
	{
		Tank* tank = _tanks[i];
		if(!tank->lived())
		{
			Location& location = _locations[rand()%_locations.size()];

			tank->relocation(location.x, location.y);
			tank->turn(location.direction);
			tank->reborn();
			return ;
		}
	}
}

inline void Robot::rebornAllTanks()
{
	for(unsigned int i=0; i<_tanks.size(); i++)
	{
		Tank* tank = _tanks[i];
		Location& location = _locations[rand()%_locations.size()];

		tank->relocation(location.x, location.y);
		tank->turn(location.direction);
		tank->reborn();
	}
}

inline void Robot::update(unsigned int dt)
{
	Object::update(dt);

	for(unsigned int i=0; i<_tanks.size(); i++)
	{
		Tank* tank = _tanks[i];

		if(!tank->moving() && tank->actived() && tank->lived())
		{
			if(rand()%100 < 15)
				tank->turn((Direction)(rand()%4));

			if(rand()%100 < 90)
				tank->moveForword();

			if(rand()%100 < 15)
				tank->fire();
		}
	}
}

#endif
