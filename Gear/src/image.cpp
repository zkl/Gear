#include "image.h"

	
void Image::resize(int w, int h)
{
	if(w <= 0 || h <= 0)
		return ;

	SDL_Surface* surface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);

	SDL_Surface* abgr = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_ABGR8888, 0);
	SDL_FreeSurface(surface);
	surface = abgr;

	SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
	SDL_FillRect(surface, 0, SDL_MapRGBA(surface->format, 0, 0, 0, 0));

	this->draw(surface);

	if(_surface != 0)
		SDL_FreeSurface(_surface);

	_surface = surface;
	_update = true;
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

	SDL_RenderCopy(renderer, _texture, &srcRect, &dstRect);  
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

		SDL_BlitSurface(_surface, &srcrect, surface, &desrect);
	}
}
