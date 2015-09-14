#include "imagelayer.h"

ImageLayer::ImageLayer(const char* file)
	: _x(0),
	_y(0)
{
	_image.load(file);
}


void ImageLayer::copy(SDL_Surface * surface)
{
	_image.draw(surface, _x, _y);
}
