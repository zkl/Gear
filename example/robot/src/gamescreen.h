#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include "src/tilemap/tilemap.h"
#include "src/route/astar/astar.h"
#include "src/screen.h"
#include "src/world.h"
#include "src/movie.h"
#include "robot.h"

class GameScreen : public Screen
{
public:
	virtual bool init();
	virtual void draw(SDL_Renderer* renderer);
	virtual void update(unsigned int dt);
	virtual void handleEvent(const SDL_Event& event);

private:
	Movie _target;
	Movie _bob;
	Robot _robot;
	World _world;
	AStar _route;
	TileMap _tilemap;
};


#endif
