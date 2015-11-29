#ifndef GAME_H
#define GAME_H

#include "../../../src/screen.h"
#include "../../../src/world.h"
#include "../../../src/tilemap/tilemap.h"
#include "../../../src/movie.h"
#include "../../../src/spritesheet.h"

class Game : public Screen
{
public:
	virtual bool init();
	virtual void draw(SDL_Renderer* render);
	virtual void update(unsigned int dt);
	virtual void handleEvent(const SDL_Event& event);

private:
	Image _image;
	Movie _movie;
	World _world;
	TileMap _tilemap;
};

inline bool Game::init()
{
	_world.setActive();

	_image.load("a.jpg");
	return true;
}

inline void Game::draw(SDL_Renderer* render)
{
	_image.draw(render);
	_world.draw(render);
}

inline void Game::update(unsigned int dt)
{
	_world.update(dt);
}

inline void Game::handleEvent(const SDL_Event& event)
{
}

#endif
