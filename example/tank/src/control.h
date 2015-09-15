#ifndef CONTROL_H
#define CONTROL_H

#include <vector>
#include "src/tilemap/tilemap.h"
#include "src/movie.h"
#include "src/world.h"
#include "bullet.h"
#include "tank.h"

class Control
{
public:
	bool init();
	void setMap(TileMap* tilemap);
	void setWorld(World* world);
	void update(int dt);
	void setPlayer(Tank* player);
	void createTank(int x, int y);

private:
	TileMap* _tilemap;
	World* _world;
	std::vector<Bullet*> _bullets;
	std::vector<Tank* >  _tanks;
	std::vector<Movie*>  _bobs;

	std::vector<Bullet* > _unuserdBullets;
	std::vector<Tank* > _unuserdtanks;
};

inline void Control::setMap(TileMap* tilemap)
{
	_tilemap = tilemap;
}

inline void Control::setWorld(World* world)
{
	_world = world;
}

#endif
