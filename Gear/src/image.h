#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "drawable.h"

class Image : public Drawable
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

	void copy(const Image& other, int x, int y, int w = 0, int h = 0);
	void draw(SDL_Surface* surface, int x = 0, int y = 0, int w = 0, int h = 0) const;
	void draw(SDL_Renderer * renderer, int x = 0, int y = 0, int w = 0, int h = 0);
	void drawEx(SDL_Surface* surface, int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) const;

	SDL_Surface* surface();

private:
	bool _update;
	SDL_Texture * _texture;
	SDL_Surface * _surface;
};

inline Image::Image() : 
	_surface(0),
	_texture(0),
	_update(true)
{
}

inline Image::Image(const char* file) : 
	_surface(0),
	_texture(0),
	_update(true)
{
	_surface = IMG_Load(file);
}

inline bool Image::load(const char* file)
{
	_update = true;
	_surface = IMG_Load(file);

	return _surface == 0;
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
