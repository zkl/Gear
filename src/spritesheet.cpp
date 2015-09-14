#include "spritesheet.h"

SpriteSheet::SpriteSheet() : 
	_update(true), 
	_surface(0), 
	_w(0), 
	_h(0), 
	_luptime(0), 
	_texture(0), 
	_fps(60), 
	_step(0), 
	_frames(0), 
	_playing(false) 
{
}

SDL_Surface * SpriteSheet::createSurface(int w, int h)
{
	if(_surface)
	{
		SDL_Surface * surface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
		//SDL_Surface * abgr8888 = SDL_ConvertSurfaceFormat(surface,
		//	SDL_PIXELFORMAT_ABGR8888, 0);

		//SDL_FreeSurface(surface);
		//surface = abgr8888

		//SDL_SetSurfaceBlendMode(abgr8888, SDL_BLENDMODE_BLEND);
		
		SDL_Rect rect;
		rect.x = 0;
		rect.y = 0;
		rect.w = _surface->w;
		rect.h = _surface->h;
		SDL_BlitSurface(_surface, &rect, surface, &rect);

		SDL_FreeSurface(_surface);
		_surface = surface;
	}
	else
	{
		SDL_Surface * surface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);

		_surface = SDL_ConvertSurfaceFormat(surface, 
			SDL_PIXELFORMAT_ABGR8888, 0);

		SDL_FreeSurface(surface);

		SDL_SetSurfaceBlendMode(_surface, SDL_BLENDMODE_BLEND);
		SDL_FillRect(_surface, 0, SDL_MapRGBA(_surface->format, 0, 0, 0, 0));
	}
	return _surface;
}

void SpriteSheet::addFrame (const char * resources, int x, int y, int w, int h)
{
	SDL_Surface * surface = IMG_Load(resources);
	if(_surface)
		this->createSurface(_surface->w+w, _surface->h);
	else
		this->createSurface(w, h);

	if(_surface == 0)
		return ;

	_w = w;
	_h = h;
	_frames += 1;

	SDL_Rect desrect;
	SDL_Rect srcrect;

	desrect.x = _surface->w-w;
	desrect.y = 0;
	desrect.w = w;
	desrect.h = h;

	srcrect.x = x;
	srcrect.y = y;
	srcrect.w = w;
	srcrect.h = h;

	SDL_BlitSurface(surface, &srcrect, _surface, &desrect);
	_update = true;

	SDL_FreeSurface(surface);
}

void SpriteSheet::addFrames(const char * resources, int x, int y, int w, int h,
	int column, int frames)
{
	SDL_Surface * surface = IMG_Load(resources);

	if(_surface)
		this->createSurface(_surface->w+w*frames, _surface->h);
	else
		this->createSurface(w*frames, h);

	if(_surface == 0)
		return ;

	_w = w;
	_h = h;
	_frames += frames;

	for(int i=0; i<frames; i++)
	{
		SDL_Rect desrect;
		SDL_Rect srcrect;

		desrect.x = _surface->w-w*(frames-i);
		desrect.y = 0;
		desrect.w = w;
		desrect.h = h;

		if(i%column < 1)
			srcrect.x = x+(i%column)*w;
		else
			srcrect.x = (i%column)*w;

		srcrect.y = (i/column)*h;
		srcrect.w = w;
		srcrect.h = h;
		SDL_BlitSurface(surface, &srcrect, _surface, &desrect);
	}

	_update = true;
	SDL_FreeSurface(surface);
}

void SpriteSheet::update(unsigned int dt)
{
	if(!_playing)
		return ;

	_luptime += dt;
	if(_luptime >= 1000/_fps)
	{
		_luptime = 0;
		++_step >= _frames ? _step = 0 : 0;
	}
}

void SpriteSheet::draw(SDL_Renderer * renderer)
{
	if(_update) 
	{
		_update = false;
		if(_texture != 0)
			SDL_DestroyTexture(_texture);

		_texture = SDL_CreateTextureFromSurface(renderer, _surface);  
	}

	if (NULL == _texture || _frames <= 0) 
		return ;

	SDL_Rect dstRect;
	SDL_Rect srcRect;
	
	dstRect.w = _w;
	dstRect.h = _h;
	dstRect.x = _x;
	dstRect.y = _y;

	srcRect.w = _w;
	srcRect.h = _h;
	srcRect.x = (_step%_frames)*_w;
	srcRect.y = (_step/_frames)*_h;

	SDL_RenderCopy(renderer, _texture, &srcRect, &dstRect);  
}
