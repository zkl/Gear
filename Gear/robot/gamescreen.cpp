#include "gamescreen.h"

bool GameScreen::init()
{
	_tilemap.load("game.tmx");
	_robot.setTileMap(&_tilemap);

	_world.appendChild(&_tilemap);
	_world.appendChild(&_robot);
	_world.appendChild(&_target);
	_world.init();

	Image* frame = new Image("block.png");
	_target.addFrame(frame);
	frame->def();

	return true;
}

void GameScreen::update(unsigned int dt)
{
	_world.update(dt);
}

void GameScreen::draw(SDL_Renderer* render)
{
	_world.draw(render);
}

void GameScreen::handleEvent(const SDL_Event& event)
{
	switch (event.type)
	{	
		case SDL_MOUSEBUTTONDOWN:
		{
			_target.setPosition(event.motion.x, event.motion.y);
			break;
		}
		case SDL_MOUSEMOTION:
		{
			break;
		}
		case SDL_KEYDOWN:
		{
			const Uint8* sta = SDL_GetKeyboardState(0);

			if(sta[SDL_SCANCODE_W])
				_robot.turnUp();
			if(sta[SDL_SCANCODE_S])
				_robot.turnDown();
			if(sta[SDL_SCANCODE_A])
				_robot.turnLeft();
			if(sta[SDL_SCANCODE_D])
				_robot.turnRight();

			break;
		}
	default:
		break;
	}
}

