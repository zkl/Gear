#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include "../src/tilemap/tilemap.h"
#include "../src/screen.h"
#include "../src/world.h"
#include "../src/movie.h"
#include "robot.h"

class GameScreen : public Screen
{
public:
	virtual bool init();
	virtual void draw(SDL_Renderer* render);
	virtual void update(unsigned int dt);
	virtual void handleEvent(const SDL_Event& event);

private:
	Movie _target;
	Robot _robot;
	World _world;
	TileMap _tilemap;
};


#endif
