#ifndef G_IMAGE_H
#define G_IMAGE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "gpainter.h"

class GImage
{
	friend class GPainter;

public:
	GImage();
	GImage(const char* file);

	bool load(const char* file);
	bool empty();

	int  width();
	int  height();
	void resize(int w, int h);
	void rotation(double angle);

	//void copy(const GImage& other, int x, int y, int w = 0, int h = 0);
private:
	bool _update;
	double _angle;

	SDL_Point _center;
	SDL_RendererFlip _flip;
	GPainter _painter;
	SDL_Texture * _texture;
	SDL_Surface * _surface;
};


inline GImage::GImage() : 
	_surface(0),
	_texture(0),
	_angle(0.0),
	_update(true),
	_painter(this),
	_flip(SDL_FLIP_NONE)
{
	_center.x = 0;
	_center.y = 0;
}

inline GImage::GImage(const char* file) : 
	_texture(0),
	_update(true),
	_painter(this),
	_surface(0)
{
	if(file != 0 || *file != 0)
		this->load(file);
}


inline bool GImage::empty()
{
	return _surface == 0;
}

inline int GImage::width()
{
	return _surface->w;
}

inline int GImage::height()
{
	return _surface->h;
}

#endif
