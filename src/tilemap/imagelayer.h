#ifndef IMAGE_LAYER_H
#define IMAGE_LAYER_H

#include <string>
#include <SDL2/SDL_image.h>
#include "../image.h"

class ImageLayer
{
public:
	ImageLayer(const char* file);
	void move(int x, int y){_x = x; _y=y;}
	void copy(SDL_Surface * surface);

private:

	int _x, _y;
	std::string _name;
	Image _image;
};

#endif
