#include "src/route/astar/astar.h"
#include "gamescreen.h"
#include <stdlib.h>
#include <time.h>

bool GameScreen::init()
{
	_tilemap.load("map.tmx");

	_world.appendChild(&_tilemap);
	_world.appendChild(&_target);
	_world.appendChild(&_bob);
	_world.appendChild(&_bullet);
	_world.init();

	_route.resize(_tilemap.tilsetColum(), _tilemap.tilsetRow());

	Image image("target.png");
	_target.addFrames(&image, 0, 0, 16, 16, 6, 6);

	Image bobimg("bob.png");
	_bob.addFrames(&bobimg, 0, 0, 64, 64, 6, 6);
	_bob.setFps(15);
	
	_target.loop();
	_target.play();
	_target.setFps(15);


	_bullet.setPosition(100, 100);

	srand(time(0));
	return true;
}

void GameScreen::update(unsigned int dt)
{
	_world.update(dt);
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

			_target.setPosition(x-x%w, y-y%h);
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
				_bullet.setPosition(100, 100);
				_bullet.emit(0);
			}

			break;
		}
	default:
		break;
	}
}

