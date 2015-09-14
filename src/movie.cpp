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
	if(!_playing)
		return ;

	_uptime += dt;
	while(_uptime >= _interval)
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
