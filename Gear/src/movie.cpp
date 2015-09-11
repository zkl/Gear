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
