#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ref.h"

class Image : public Ref
{
public:
	Image();
	Image(const char* file);
	~Image();

	bool load(const char* file);
	bool empty();
	void resize(int w, int h);
	void update();
	int  width();
	int  height();

	void rotation(double angle);
	void setOrigin(int x, int y);
	void copy(const Image& other, int x, int y, int w = 0, int h = 0);
	void draw(SDL_Surface* surface, int x = 0, int y = 0, int w = 0, int h = 0) const;
	void draw(SDL_Renderer * renderer, int x = 0, int y = 0, int w = 0, int h = 0);
	void drawEx(SDL_Surface* surface, int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) const;

	//void fill(SDL_Rect* rect, Color* c);

	SDL_Surface* surface();

private:
	bool _update;
	double _angle;
	SDL_Point _center;
	SDL_RendererFlip _flip;
	SDL_Texture * _texture;
	SDL_Surface * _surface;
};

inline Image::Image() : 
	_surface(0),
	_texture(0),
	_angle(0.0),
	_update(true),
	_flip(SDL_FLIP_NONE)
{
	_center.x = 0;
	_center.y = 0;
}

inline Image::Image(const char* file) : 
	_texture(0),
	_update(true)
{
	_surface = IMG_Load(file);
}

inline bool Image::load(const char* file)
{
	if(_surface != 0)
		SDL_FreeSurface(_surface);

	_update = true;
	_surface = IMG_Load(file);
	if(_surface == 0)
	{
		printf("Image::load -> %s\n", file);
		return false;
	}

	_center.x = _surface->w / 2;
	_center.y = _surface->h / 2;
	
	return true;
}

inline Image::~Image()
{
	if(_surface != 0)
		SDL_FreeSurface(_surface);

	if(_texture != 0)
		SDL_DestroyTexture(_texture);

	_surface = 0;
	_texture = 0;
}

inline void Image::rotation(double angle)
{
	_angle = angle;
}

inline void Image::setOrigin(int x, int y)
{
	_center.x = x;
	_center.y = y;
}

inline bool Image::empty()
{
	return _surface == 0;
}

inline void Image::update()
{
	_update = true;
}

inline int Image::width()
{
	return _surface->w;
}

inline int Image::height()
{
	return _surface->h;
}

inline SDL_Surface* Image::surface()
{
	return _surface;
}

#endif
