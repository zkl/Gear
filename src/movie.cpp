#include "image.h"
#include "movie.h"

void Movie::addFrames(Image* image, int x, int y, int w, int h,
	int column, int frames)
{
	for(int i=0; i<frames; i++)
	{
		Image* img = new Image();
		img->resize(w, h);
		img->copy(*image, x+(i%column)*w, y+(i/column)*h, w, h);
		this->addFrame(img);

		img->def();
	}
}

void Movie::update(unsigned int dt)
{
	_uptime += dt;
	if(_uptime >= _interval)
	{
		_uptime -= _interval;
		if((unsigned int)++_frame >= _frames.size())
		{
			_frame = 0;
			if(!_loop)
				_playing = false;
		}
	}
}

void Movie::draw(SDL_Renderer* renderer)
{
	_frames[_frame]->draw(renderer, _x, _y);
}
