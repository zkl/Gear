#include "src/director.h"
#include "startscreen.h"

bool StartScreen::init()
{
	return _image.load("menu.png");
}

void StartScreen::begin()
{
	_uptime = 0;
	_height = _image.height();
}

void StartScreen::update(unsigned int dt)
{
	_uptime += dt;
	if(_height > 0)
		_height -= 2;
}

void StartScreen::handleEvent(const SDL_Event& event)
{
	if(_uptime < 1000)
		return ;

	if(event.type == SDL_KEYDOWN)
		Director::getDirector()->changeScreen("Game");
}

void StartScreen::draw(SDL_Renderer* randerer)
{
	_image.draw(randerer, 0, _height);
}
