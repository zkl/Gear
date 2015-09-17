#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include "src/tilemap/tilemap.h"
#include "src/route/astar/astar.h"
#include "src/screen.h"
#include "src/world.h"
#include "src/movie.h"
#include "tank.h"
#include "robot.h"

class GameScreen : public Screen
{
public:
	virtual bool init();
	virtual void begin();
	virtual void end();
	virtual void draw(SDL_Renderer* renderer);
	virtual void update(unsigned int dt);
	virtual void handleEvent(const SDL_Event& event);

	static bool tankBlowUp(int id, void* data, void* param);
private:
	int _livedTanks;
	Tank  _tank;
	World _world;
	TileMap _tilemap;
	std::vector<Robot*> _robots;
};


#endif
