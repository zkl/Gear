#include <stdio.h>
#include "image.h"

void Image::resize(int w, int h)
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

	if(_surface != 0)
	{
		this->drawEx(surface, 0, 0, w, h, 0, 0, _surface->w, _surface->h);
		SDL_FreeSurface(_surface);
	}

	_update = true;
	_surface = surface;

	_center.x = _surface->w / 2;
	_center.y = _surface->h / 2;
}

void Image::copy(const Image& other, int x, int y, int w, int h)
{
	if(other._surface == 0)
		return ;

	if(_surface == 0)
		this->resize(w, h);

	w = w <= 0? other._surface->w-x : w;
	h = h <= 0? other._surface->h-y : h;

	_update = true;

	SDL_Rect desrect;
	SDL_Rect srcrect;

	desrect.x = 0;
	desrect.y = 0;
	desrect.w = w;
	desrect.h = h;

	srcrect.x = x;
	srcrect.y = y;
	srcrect.w = w;
	srcrect.h = h;

	SDL_BlitSurface(other._surface, &srcrect, _surface, &desrect);
}

void Image::draw(SDL_Surface* surface, int x, int y, int w, int h) const
{
	if(_surface != 0)
	{
		w = w <= 0? _surface->w : w;
		h = h <= 0? _surface->h : h;
		drawEx(surface, x, y, w, h, 0, 0, w, h);
	}
}

void Image::draw(SDL_Renderer * renderer, int x, int y, int w, int h)
{
	if(_surface == 0)
		return ;

	if(_update) 
	{
		_update = false;
		if(_texture != 0)
		//	SDL_UpdateTexture(_texture, 0, _surface->pixels, _surface->pitch);
			SDL_DestroyTexture(_texture);

		_texture = SDL_CreateTextureFromSurface(renderer, _surface);  
	}

	if (NULL == _texture) 
		return ;

	SDL_Rect dstRect;
	SDL_Rect srcRect;

	w = w <= 0? _surface->w : w;
	h = h <= 0? _surface->h : h;
	
	dstRect.w = w;
	dstRect.h = h;
	dstRect.x = x;
	dstRect.y = y;

	srcRect.w = w;
	srcRect.h = h;
	srcRect.x = 0;
	srcRect.y = 0;

	if(_angle == 0)
		SDL_RenderCopy(renderer, _texture, &srcRect, &dstRect);
	else
		SDL_RenderCopyEx(renderer, _texture, &srcRect, &dstRect, _angle, &_center, _flip);
}

void Image::drawEx(SDL_Surface* surface, int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) const
{
	if(_surface != 0)
	{
		SDL_Rect desrect;
		SDL_Rect srcrect;

		desrect.x = x1;
		desrect.y = y1;
		desrect.w = w1;
		desrect.h = h1;

		srcrect.x = x2;
		srcrect.y = y2;
		srcrect.w = w2;
		srcrect.h = h2;

		if(w1 == w2 && h1 == h2)
		{
			SDL_BlitSurface(_surface, &srcrect, surface, &desrect);
		}
		else
		{
			// @todo SDL_BlitScaled PNGÍ¼Æ¬Ê§°Ü
			//SDL_BlitScaled(_surface, &srcrect, surface, &desrect);
			SDL_BlitSurface(_surface, &srcrect, surface, &desrect);
		}
	}
}

void Image::fill(Color* c, const SDL_Rect* rect)
{
	SDL_FillRect(_surface, rect, SDL_MapRGBA(_surface->format, (Uint8)c->r(), (Uint8)c->g(), (Uint8)c->b(), (Uint8)c->a()));
	_update = true;
}