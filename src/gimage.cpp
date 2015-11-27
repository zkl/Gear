#include "gimage.h"


void GImage::resize(int w, int h)
{
	if(w <= 0 || h <= 0)
		return ;

	Uint32 rmask, gmask, bmask, amask;
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
	#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
	#endif

	SDL_Surface* surface = SDL_CreateRGBSurface(0, w, h, 32, rmask, gmask, bmask, amask);
	if(surface == 0)
		return ;

	SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
	SDL_FillRect(surface, 0, SDL_MapRGBA(surface->format, 0, 0, 0, 0));

	_update = true;
	_surface = surface;

	_center.x = _surface->w / 2;
	_center.y = _surface->h / 2;
}

