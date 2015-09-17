#include "src/director.h"
#include "startscreen.h"

bool StartScreen::init()
{
	return _message.load("menu.png") && _image.load("bg.png");
}

void StartScreen::begin()
{
	_uptime = 0;
	_height = _image.height();
}

void StartScreen::update(unsigned int )
{
	if(_height > 0)
		_height -= 2;
	else
		_height = 0;
}

void StartScreen::handleEvent(const SDL_Event& event)
{
	if(_height > 0)
		return ;

	if(event.type == SDL_KEYDOWN)
		Director::getDirector()->changeScreen("Game");
}

void StartScreen::draw(SDL_Renderer* randerer)
{
	_image.draw(randerer);
	_message.draw(randerer, 0, _height);
}
