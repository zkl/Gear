#include "gamescreen.h"

bool GameScreen::init()
{
	_tilemap.load("map.tmx");
	_world.appendChild(&_tilemap);
	_world.appendChild(&_snake);
	_world.init();

	_snake.uplevel();
	_snake.uplevel();
	_snake.uplevel();
	_snake.uplevel();

	return true;
}

void GameScreen::update(unsigned int dt)
{
	_world.update(dt);
	if(_snake.dead() || 
		_tilemap.getGid(_snake.x(), _snake.y()) != 0 || 
		_tilemap.getGid(_snake.x()+_tilemap.tilsetWidth()-1, _snake.y()+_tilemap.tilsetHeight()-1))
	{
		_snake.setActive(false);
	}
}

void GameScreen::draw(SDL_Renderer* render)
{
	_world.draw(render);
}

void GameScreen::handleEvent(const SDL_Event& event)
{
	switch (event.type)
	{
		case SDL_MOUSEMOTION:
		{
			if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) 
			{
				//_tilemap.move(event.motion.xrel, event.motion.yrel);
			}
			break;
		}
		case SDL_KEYDOWN:
		{
			const Uint8* sta = SDL_GetKeyboardState(0);
			if(sta[SDL_SCANCODE_W])
				_snake.turnUp();
			if(sta[SDL_SCANCODE_S])
				_snake.turnDown();
			if(sta[SDL_SCANCODE_A])
				_snake.turnLeft();
			if(sta[SDL_SCANCODE_D])
				_snake.turnRight();

			if(sta[SDL_SCANCODE_R])
			{
				_snake.setActive();
				_snake.setPosition(0, 0);

				_snake.init();
				_snake.uplevel();
				_snake.uplevel();
				_snake.uplevel();
				_snake.uplevel();
			}
			break;
		}
	default:
		break;
	}
}
