#include "src/route/astar/astar.h"
#include "gamescreen.h"
#include <stdlib.h>
#include <time.h>

bool GameScreen::init()
{
	_tilemap.load("map.tmx");

	_world.appendChild(&_tilemap);
	_world.init();

	_control.setWorld(&_world);
	_control.setMap(&_tilemap);

	srand((unsigned int)time(0));
	return true;
}

void GameScreen::update(unsigned int dt)
{
	_world.update(dt);
	_control.update(dt);
}

void GameScreen::draw(SDL_Renderer* renderer)
{
	_world.draw(renderer);
}

void GameScreen::handleEvent(const SDL_Event& event)
{
	switch (event.type)
	{	
		case SDL_MOUSEBUTTONDOWN:
		{
			int w = _tilemap.tilsetWidth();
			int h = _tilemap.tilsetHeight();
			int x = event.motion.x;
			int y = event.motion.y;
			break;
		}
		case SDL_MOUSEMOTION:
		{
			break;
		}
		case SDL_KEYDOWN:
		{
			const Uint8* sta = SDL_GetKeyboardState(0);
			if(sta[SDL_SCANCODE_T])
			{
				_control.createTank(256, 256);
			}

			break;
		}
	default:
		break;
	}
}

