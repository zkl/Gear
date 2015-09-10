#ifndef MENU_H
#define MENU_H

#include "../../src/screen.h"
#include "../../src/image.h"

class Menu : public Screen
{
public:

	virtual bool init();
	virtual void draw(SDL_Renderer * randerer);

private:
	Image* _image;
};

inline bool Menu::init()
{
	_image = new Image();
	_image->resize(100, 100);

	Image image;
	image.load("image/bg.jpg");

	image.drawEx(_image->surface(), 10, 10, 100, 100, 0, 0, 100, 100);

	return true;
}

inline void Menu::draw(SDL_Renderer * randerer)
{
	_image->draw(randerer);
}

#endif