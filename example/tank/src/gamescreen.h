#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include "src/tilemap/tilemap.h"
#include "src/route/astar/astar.h"
#include "src/screen.h"
#include "src/world.h"
#include "src/movie.h"
#include "tank.h"
#include "bullet.h"
#include "control.h"

class GameScreen : public Screen
{
public:
	virtual bool init();
	virtual void draw(SDL_Renderer* renderer);
	virtual void update(unsigned int dt);
	virtual void handleEvent(const SDL_Event& event);

private:
	World _world;
	TileMap _tilemap;
	Control _control;
};


#endif
