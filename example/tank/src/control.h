#ifndef CONTROL_H
#define CONTROL_H

#include <vector>
#include "src/tilemap/tilemap.h"
#include "bullet.h"
#include "tank.h"

class Control
{
public:
	bool init();
	void setMap(TileMa* tilemap);
	void update(int dt);

private:
	std::vector<Bullet* > _bullets;
	std::vector<Tank* >   _tanks;

	std::vector<Bullet* > _unuserdBullets;
	std::vector<Tank* > _unuserdtanks;
};
#endif
